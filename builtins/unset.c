/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:28:57 by paula             #+#    #+#             */
/*   Updated: 2023/12/26 16:42:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_node(t_env *node_to_del, t_env **my_env)
{
	t_env	*temp;
	t_env	*prev;

	temp = (*my_env);
	prev = NULL;
	while (temp)
	{
		if (temp == node_to_del)
		{
			prev->next = temp->next;
			free(temp->key);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	remove_env(char *args, t_env **my_env)
{
	t_env	*aux;

	aux = *my_env;
	while (aux)
	{
		if (!ft_strncmp(args, aux->key, ft_strlen(args)))
		{
			printf("a palavra eh %s\n", aux->key);
			if (aux->key[ft_strlen(args)] == '=')
				return (del_node(aux, my_env));
		}
		aux = aux->next;
	}
}

int	unset(char **args, t_env **my_env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env(args[i], my_env);
		i++;
	}
	return (0);
}
