/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2024/01/30 17:48:24 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_dados *data, t_env **my_env)
{
	int	exit_status;

	rl_clear_history();
	ft_free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	if (!data || (!data->comando[1] && data))
	{
		free_list(&data);
		exit(EXIT_SUCCESS);
	}
	if (data->comando[2])
	{
		exit_status = ft_atoi(data->comando[1]);
		ft_exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	if (!ft_isnumber(data->comando[1]))
	{
		exit_status = ft_atoi(data->comando[1]);
		ft_exit_with_error("exit", "numeric argument required", 2);
	}
	exit_status = ft_atoi(data->comando[1]);
	free_list(&data);
	exit(exit_status);
}
