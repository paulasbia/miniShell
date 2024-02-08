/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:36:33 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_n(char *args)
{
	if (strncmp(args, "-n", 3))
		return (0);
	return (1);
}

int	ft_echo(t_dados *data)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (data->cmd[i] && ft_check_n(data->cmd[i]))
	{
		new_line = 1;
		i++;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], STDOUT_FILENO);
		if (data->cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
