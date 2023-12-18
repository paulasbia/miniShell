/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2023/12/18 10:33:29 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(char **arg, t_env **my_env)
{
	int	exit_status;

	(void)arg;
	rl_clear_history();
	free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	exit_status = 0;
	exit(exit_status);
}
