/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 10:10:45 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **arg, t_env **my_env)
{
	int	exit_status;

	rl_clear_history();
	ft_free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	if (!arg || (!arg[1] && arg))
		exit(EXIT_SUCCESS);
	if (arg[2])
	{
		exit_status = ft_atoi(arg[1]);
		ft_exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	if (!ft_isnumber(arg[2]))
	{
		exit_status = ft_atoi(arg[1]);
		ft_exit_with_error("exit", "numeric argument required", 2);
	}
	exit_status = ft_atoi(arg[1]);
	exit(exit_status);
}
