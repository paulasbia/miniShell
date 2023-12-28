/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:24:42 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 10:09:57 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_env(t_env **my_env)
{
	t_env	*aux;
	t_env	*next;

	aux = *my_env;
	while (aux)
	{
		free(aux->key);
		next = aux->next;
		free(aux);
		aux = next;
	}
	my_env = NULL;
}
