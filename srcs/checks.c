/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:01 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 10:03:26 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_arg(int ac, char **av)
{
	if (av && ac > 1)
	{
		ft_putstr_fd("Minishell invalid arguments\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (0);
}
