/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:08:28 by paula             #+#    #+#             */
/*   Updated: 2024/01/12 15:56:41 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_builtin(char **args, t_env **minienv, int *fds)
{
	char	*command;

	command = args[0];
	if (str_equal(command, "pwd"))
		return (ft_pwd(fds));
	if (str_equal(command, "exit"))
		return (ft_exit(args, minienv));
	if (str_equal(command, "echo"))
		return (ft_echo(args));
	if (str_equal(command, "env"))
		return (ft_env(*minienv));
	if (str_equal(command, "unset"))
		return (ft_unset(args, minienv));
	if (str_equal(command, "export"))
		return (ft_export(args, minienv));
	if (str_equal(command, "cd"))
		return (ft_cd(args, minienv));
	else
		return (EXIT_FAILURE);
}
