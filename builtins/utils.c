/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:37:26 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 09:08:25 by paula            ###   ########.fr       */
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

int	ft_cmd_builtin(t_dados *data)
{
	char	*command;

	command = data->comando[0];
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
	if (str_equal(command, "unset"))
		return (1);
	if (str_equal(command, "export"))
		return (1);
	if (str_equal(command, "cd"))
		return (1);
	return (0);
}
