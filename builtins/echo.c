/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:36:33 by paula             #+#    #+#             */
/*   Updated: 2023/12/19 10:51:31 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_n(char *args)
{
	int	i;

	i = 0;
	if (args[i] != '-')
		return (0);
	i++;
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (args[i] && ft_check_n(args[i]))
	{
		new_line = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
