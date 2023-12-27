/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:37:26 by paula             #+#    #+#             */
/*   Updated: 2023/12/27 10:56:07 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if (!str1 || !str2)
		return (0);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (0);
	return (ft_strncmp(str1, str2, size) == 0);
}

int	execute_builtin(char **args, t_env **minienv)
{
	char	*command;

	command = args[0];
	if (str_equal(command, "pwd"))
		return (pwd());
	if (str_equal(command, "exit"))
		return (ft_exit(args, minienv));
	if (str_equal(command, "echo"))
		return (echo(args));
	if (str_equal(command, "env"))
		return (env(*minienv));
	if (str_equal(command, "unset"))
		return (unset(args, minienv));
	if (str_equal(command, "export"))
		return (ft_export(args, minienv));
	else
		return (EXIT_FAILURE);
}

int	cmd_builtin(char **args)
{
	char	*command;

	command = args[0];
	if (!command)
		return (0);
	if (str_equal(command, "pwd"))
		return (1);
	if (str_equal(command, "exit"))
		return (1);
	if (str_equal(command, "echo"))
		return (1);
	if (str_equal(command, "env"))
		return (1);
	if (str_equal(command, "export"))
		return (1);
	return (0);
}

char	*varname(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '=' && name[i])
		i++;
	return (ft_substr(name, 0, i));
}

char	*varvalue(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i])
		i++;
	if (!value[i])
		return (NULL);
	return (&value[i + 1]);
}
