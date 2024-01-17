/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:08:28 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 10:18:06 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_builtin(t_dados *data, t_env **minienv)
{
	char	*command;

	command = data->comando[0];
	if (str_equal(command, "pwd"))
		return (ft_pwd());
	if (str_equal(command, "exit"))
		return (ft_exit(data, minienv));
	if (str_equal(command, "echo"))
		return (ft_echo(data));
	if (str_equal(command, "env"))
		return (ft_env(*minienv));
	// if (str_equal(command, "unset"))
	// 	return (ft_unset(args, minienv));
	// if (str_equal(command, "export"))
	// 	return (ft_export(args, minienv));
	// if (str_equal(command, "cd"))
	// 	return (ft_cd(args, minienv));
	else
		return (EXIT_FAILURE);
}
