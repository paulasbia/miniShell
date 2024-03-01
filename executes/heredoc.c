/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:42:53 by paula             #+#    #+#             */
/*   Updated: 2024/03/01 11:05:32 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_sig;

static void	handle_sig_hd(int s)
{
	(void)s;
	g_sig = 1;
	close(STDIN_FILENO);
	exit(130);
}

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = &handle_sig_hd;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

t_redirect	*check_heredoc(t_dados **data, int *red_out)
{
	while (*data)
	{
		while (*red_out < (*data)->nbr_redirections)
		{
			if ((*data)->redirect[*red_out].redirect_type == 2)
			{
				return (&((*data)->redirect[*red_out]));
			}
			(*red_out)++;
		}
		*data = (*data)->next;
		*red_out = 0;
	}
	return (NULL);
}

void	ft_read_heredoc(t_redirect *redirect)
{
	char	*input_hd;
	int		fd_hd;

	fd_hd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	input_hd = readline("> ");
	while (input_hd && !str_equal(input_hd, redirect->filename))
	{
		ft_putstr_fd(input_hd, fd_hd);
		ft_putstr_fd("\n", fd_hd);
		free(input_hd);
		input_hd = readline("> ");
	}
	if (!input_hd && g_sig != 1)
		print_error_msg("warning: heredoc delimited by EOF. Wanted",
			redirect->filename);
	free(input_hd);
	close_all();
	close(fd_hd);
	if (g_sig == 1)
		exit(130);
	else
		exit(EXIT_SUCCESS);
}

int	parse_heredoc(t_dados *dados)
{
	struct s_parse_heredoc	ph;
	int						exit_code;

	exit_code = 0;
	ph.i = 0;
	ph.red_temp = check_heredoc(&dados, &(ph.i));
	while ((ph.red_temp))
	{
		ph.i++;
		ph.child_pid = fork();
		define_heredoc_signals(ph.child_pid);
		if (ph.child_pid < 0)
			ft_child_err((ph.red_temp)->filename);
		else if (!ph.child_pid)
			ft_read_heredoc(ph.red_temp);
		else
		{
			exit_code = ft_wait_exit_status(ph.child_pid);
			free((ph.red_temp)->filename);
			(ph.red_temp)->filename = ft_strdup("/tmp/heredoc");
			ft_init_signal();
			ph.red_temp = check_heredoc(&dados, &(ph.i));
		}
	}
	return (exit_code);
}
