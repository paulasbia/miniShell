/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:05:18 by paula             #+#    #+#             */
/*   Updated: 2024/02/05 20:46:29 by paula            ###   ########.fr       */
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
	if (!ft_seach_node("OLDPWD", my_list))
		ft_add_list("OLDPWD", &my_list);
	return (my_list);
}
