/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:30 by paula             #+#    #+#             */
/*   Updated: 2024/01/02 15:09:11 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_list(char *key, t_env **my_list)
{
	struct s_env	*new_node;
	struct s_env	*aux_node;

	new_node = malloc(sizeof(struct s_env));
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

int	main(int ac, char **av, char **env)
{
	t_env	*init_env;

	ft_check_arg(ac, av);
	init_env = init_minienv(env);
	return (minishell(init_env));
}
