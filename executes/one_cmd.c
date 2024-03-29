/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2024/02/20 15:57:42 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	back_saved_fd(int saved_fd[2])
{
	if (saved_fd[0] != -1)
	{
		dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
	}
	if (saved_fd[1] != -1)
	{
		dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
	}
}

int	ft_execute_child(t_dados *data, t_env *my_env)
{
	pid_t	child_pid;

	child_pid = fork();
	ft_def_signal(child_pid);
	if (child_pid < 0)
		ft_child_err(data->cmd[0]);
	if (!child_pid)
		ft_exec_child_process(data, my_env);
	return (ft_wait_exit_status(child_pid));
}

int	ft_one_cmd(t_dados *data, t_env **my_env)
{
	int	exit_status;
	int	saved_fd[2];

	if (!handle_redirects(data, &saved_fd[0]))
	{
		back_saved_fd(saved_fd);
		return (EXIT_FAILURE);
	}
	if (ft_cmd_builtin(data))
		exit_status = ft_execute_builtin(data, my_env);
	else
		exit_status = ft_execute_child(data, *my_env);
	back_saved_fd(saved_fd);
	return (exit_status);
}
