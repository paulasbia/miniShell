/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:28:57 by paula             #+#    #+#             */
/*   Updated: 2023/12/26 17:50:50 by paula            ###   ########.fr       */
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
			printf("a palavra eh %s\n", aux->key); // comentario a retirar
			if (aux->key[ft_strlen(args)] == '=')
				return (del_node(aux, my_env));
		}
		aux = aux->next;
	}
}

int	unset(char **args, t_env **my_env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = EXIT_SUCCESS;
	while (args[i])
	{
		printf("eh %s\n", args[i]);
		if (!ft_strncmp(args[i], "-", 1) && args[i][1]) // unico erro encontrado no bash, verificar na 42
		{
			print_error_var("unset", args[i]);
			exit_status = 2;
		}
		remove_env(args[i], my_env);
		i++;
	}
	return (exit_status);
}
