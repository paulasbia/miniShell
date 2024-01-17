/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 13:55:56 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_child(t_dados *data, t_env *my_env)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	ft_def_signal(child_pid);
	if (child_pid < 0)
		ft_child_err("fork", data->comando[0]);
	if (!child_pid)
		ft_exec_child_process(data->comando, my_env);
	waitpid(child_pid, &status, 0);
	return (EXIT_FAILURE);
}

// mudar a funcao free para o da Tais aqui
int	ft_one_cmd(t_dados *data, t_env **my_env)
{
	int	exit_status;

	if (ft_cmd_builtin(data))
		exit_status = ft_execute_builtin(data, my_env);
	else
		exit_status = ft_execute_child(data, *my_env);
	ft_free_data(&data);
	return (exit_status);
}
