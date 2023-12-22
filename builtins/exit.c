/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2023/12/22 09:43:46 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(char **arg, t_env **my_env)
{
	int	exit_status;

	rl_clear_history();
	free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	if (!arg || (!arg[1] && arg))
		exit(EXIT_SUCCESS);
	if (arg[2])
	{
		exit_status = ft_atoi(arg[1]);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	exit_status = ft_atoi(arg[1]);
	exit(exit_status);
}
