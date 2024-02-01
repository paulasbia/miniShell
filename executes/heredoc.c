/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:42:53 by paula             #+#    #+#             */
/*   Updated: 2024/02/01 09:59:59 by paula            ###   ########.fr       */
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

t_dados	*parse_heredoc(t_dados *dados)
{
	char	*input;
	t_dados	*temp;
	int		i;
	int		fd;
	pid_t	child_pid;

	if (check_heredoc(dados, &temp, &i))
	{
		child_pid = fork();
		define_heredoc_signals(child_pid);
		if (child_pid < 0)
			ft_child_err("fork - heredoc", temp->redirect->filename);
		else if (!child_pid)
		{
			fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
			input = readline("> ");
			while (input && !str_equal(input, temp->redirect[i].filename))
			{
				ft_putstr_fd(input, fd);
				ft_putstr_fd("\n", fd);
				free(input);
				input = readline("> ");
			}
			free(input);
			close(fd);
            temp->redirect[i].filename = "/tmp/heredoc";
			exit(EXIT_SUCCESS);
		}
        else
        {
            ft_wait_exit_status(child_pid);
            ft_init_signal();
        }
	}
	return (dados);
}
