/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:42:53 by paula             #+#    #+#             */
/*   Updated: 2024/02/01 11:08:54 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

int	check_heredoc(t_dados *data, t_dados **data_out, int *red_out)
{
	int	i;

	*data_out = NULL;
	i = 0;
	while (data)
	{
		while (i < data->nbr_redirections)
		{
			if (data->redirect->redirect_type == 2)
			{
				*red_out = i;
				*data_out = data;
			}
			i++;
		}
		data = data->next;
		i = 0;
	}
	return (*data_out != NULL);
}

void	ft_read_heredoc(t_dados *temp, int *i)
{
	char	*input_hd;
	int		fd_hd;

	fd_hd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	input_hd = readline("> ");
	while (input_hd && !str_equal(input_hd, temp->redirect[*i].filename))
	{
		ft_putstr_fd(input_hd, fd_hd);
		ft_putstr_fd("\n", fd_hd);
		free(input_hd);
		input_hd = readline("> ");
	}
	free(input_hd);
	close(fd_hd);
	exit(EXIT_SUCCESS);
}

t_dados	*parse_heredoc(t_dados *dados)
{
	t_dados	*temp;
	int		i;
	pid_t	child_pid;

	if (check_heredoc(dados, &temp, &i))
	{
		child_pid = fork();
		define_heredoc_signals(child_pid);
		if (child_pid < 0)
			ft_child_err("fork - heredoc", temp->redirect->filename);
		else if (!child_pid)
		{
			ft_read_heredoc(temp, &i);
		}
		else
		{
			ft_wait_exit_status(child_pid);
			free(temp->redirect[i].filename);
			temp->redirect[i].filename = ft_strdup("/tmp/heredoc");
			ft_init_signal();
		}
	}
	return (dados);
}
