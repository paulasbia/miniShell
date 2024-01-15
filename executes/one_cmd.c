/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2024/01/15 17:13:11 by paula            ###   ########.fr       */
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
int	ft_one_cmd(t_dados *parsed, t_env **my_env)
{
//	char	**args;
	int		exit_status;

	// args = ft_split(input, ' ');
	// free(input);
	if (ft_cmd_builtin(parsed->comando))
		exit_status = ft_execute_builtin(parsed->comando, my_env);
	else
		exit_status = ft_execute_child(parsed->comando, *my_env);
	//ft_free_args(args); //limpar a lista no final
	return (exit_status);
}
