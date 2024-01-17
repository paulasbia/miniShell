/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:24:42 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 15:43:39 by paula            ###   ########.fr       */
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

// temporario, usar o da tais no parsing pq nao sei se esta correto
void	ft_free_data(t_dados *data)
{
	int	i;

	i = 0;
	if (data)
	{
		while (i < data->nbr_redirections)
		{
			free(data->redirect->filename);
			i++;
		}
		free (data->redirect);
		i = 0;
		data->nbr_redirections = 0;
		if (data->comando)
		{
			while (data->comando[i])
			{
				free(data->comando[i]);
				i++;
			}
			free(data->comando);
		}
		ft_free_data(data->next);
	}
	free(data);
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
