/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:24:42 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:22:30 by paula            ###   ########.fr       */
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

void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

void	ft_clean(char **to_clean)
{
	int	i;

	i = -1;
	while (to_clean[++i])
		free(to_clean[i]);
	free(to_clean);
}

void	exit_child(t_dados *data, t_env *my_env)
{
	rl_clear_history();
	ft_free_env(&my_env);
	free_list(&data);
	exit(EXIT_FAILURE);
}
