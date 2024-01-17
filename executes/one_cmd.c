/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 09:11:17 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_child(char **args, t_env *my_env)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	ft_def_signal(child_pid);
	if (child_pid < 0)
		ft_child_err("fork", args[0]);
	if (!child_pid)
		ft_exec_child_process(args, my_env);
	waitpid(child_pid, &status, 0);
	return (EXIT_FAILURE);
}

// precisa criar outro comando
int	ft_one_cmd(t_dados *data, t_env **my_env)
{
	int		exit_status;
	(void)my_env;

	if (ft_cmd_builtin(data))
	{
		printf("oi\n");	
		exit_status = 1;	
	}

	// 	exit_status = ft_execute_builtin(args, my_env);
	// else
	// 	exit_status = ft_execute_child(args, *my_env);
	// ft_free_args(args);
	return (exit_status);
}
