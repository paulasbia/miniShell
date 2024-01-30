/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:05:18 by paula             #+#    #+#             */
/*   Updated: 2024/01/30 09:35:33 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_list(char *key, t_env **my_list)
{
	struct s_env	*new_node;
	struct s_env	*aux_node;

	new_node = malloc(sizeof(struct s_env));
	if (new_node == NULL)
		print_error_msg(key, "malloc fail");
	new_node->key = ft_strdup(key);
	new_node->next = NULL;
	if (!*my_list)
	{
		*my_list = new_node;
		return ;
	}
	aux_node = *my_list;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}

t_env	*init_minienv(char **env)
{
	t_env	*my_list;
	int		i;

	i = 0;
	my_list = NULL;
	while (env[i])
	{
		ft_add_list(env[i], &my_list);
		i++;
	}
	return (my_list);
}
