/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:36:33 by paula             #+#    #+#             */
/*   Updated: 2024/01/12 17:19:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_n(char *args)
{
	if (strncmp(args, "-n", 3))
		return (0);
	return (1);
}

int	ft_echo(char **args, int *fds)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (args[i] && ft_check_n(args[i]))
	{
		new_line = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fds[STDOUT_FILENO]);
		if (args[i + 1])
			ft_putstr_fd(" ", fds[STDOUT_FILENO]);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", fds[STDOUT_FILENO]);
	return (0);
}
