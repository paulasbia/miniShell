/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:28:57 by paula             #+#    #+#             */
/*   Updated: 2024/01/17 10:20:34 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Aqui preciso guardar o node anterior ao meu alvo,
	por isso o prev guardara o temp, ates de ir para o next*/
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
			if (prev)
				prev->next = temp->next;
			else
				*my_env = temp->next;
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
			if (aux->key[ft_strlen(args)] == '=')
				return (del_node(aux, my_env));
		}
		aux = aux->next;
	}
}

// unico erro encontrado no bash, verificar na 42
int	ft_unset(t_dados *data, t_env **my_env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = EXIT_SUCCESS;
	while (data->comando[i])
	{
		if (!ft_strncmp(data->comando[i], "-", 1) && data->comando[i][1])
		{
			ft_print_error_var("unset", data->comando[i]);
			exit_status = 2;
		}
		remove_env(data->comando[i], my_env);
		i++;
	}
	return (exit_status);
}
