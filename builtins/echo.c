/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:36:33 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 19:51:06 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_n(char *args)
{
	int	i;

	i = 0;
	if (args[0] != '-')
		return (0);
	if (args[0] == '-' && args[i + 1] != 'n')
		return (0);
	i++;
	while (args[i])
	{
		if (args[i] == ' ' || args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_dados *data)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (data->comando[i] && ft_check_n(data->comando[i]))
	{
		new_line = 1;
		i++;
	}
	while (data->comando[i])
	{
		ft_putstr_fd(data->comando[i], STDOUT_FILENO);
		if (data->comando[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
