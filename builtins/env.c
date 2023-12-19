/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:02 by paula             #+#    #+#             */
/*   Updated: 2023/12/19 15:10:52 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_env *my_env)
{
	t_env	*temp;

	temp = my_env;
	while (temp)
	{
		if (ft_strchr(temp->key, '='))
		{
			ft_putstr_fd(temp->key, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
