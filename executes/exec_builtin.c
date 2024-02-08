/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:08:28 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_builtin(t_dados *data, t_env **minienv)
{
	char	*command;

	command = data->cmd[0];
	if (str_equal(command, "pwd"))
		return (ft_pwd());
	if (str_equal(command, "exit"))
		return (ft_exit(data, minienv));
	if (str_equal(command, "echo"))
		return (ft_echo(data));
	if (str_equal(command, "env"))
		return (ft_env(*minienv));
	if (str_equal(command, "unset"))
		return (ft_unset(data, minienv));
	if (str_equal(command, "export"))
		return (ft_export(data, minienv));
	if (str_equal(command, "cd"))
		return (ft_cd(data, minienv));
	else
		return (EXIT_FAILURE);
}
