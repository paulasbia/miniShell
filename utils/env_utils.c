/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:26:21 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 16:33:39 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_varname(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '=' && name[i])
		i++;
	return (ft_substr(name, 0, i));
}

char	*ft_varvalue(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i])
		i++;
	if (!value[i])
		return (NULL);
	return (&value[i + 1]);
}

t_env	*ft_seach_node(char *name, t_env *my_env)
{
	t_env *aux;

	aux = my_env;
	while (aux)
	{
		if (!ft_strncmp(name, aux->key, ft_strlen(name)))
		{
			if (aux->key[ft_strlen(name)] == '=')
			printf("var retornar pq %s eh igual %s\n", name, aux->key);
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	ft_update_envlist(char *name_var, char *value, t_env *my_env)
{
	t_env	*aux;
	char	*new_key;
	int		size;
	int		i;

	printf("entrou para atualizar\n");
	aux = ft_seach_node(name_var, my_env);
	if (!value)
		new_key = aux->key;
	else
	{
		free(aux->key);
		size = ft_strlen(name_var) + ft_strlen(value) + 2;
		printf("size eh %d\n", size);
		new_key = malloc(size * sizeof(char));
		i = 0;
		while (*name_var)
			new_key[i++] = *name_var++;
		printf("ate aqui eh %s\n", new_key);
		new_key[i++] = '=';
		while (*value)
			new_key[i++] = *value++;
		new_key[i] = 0;
		aux->key = new_key;
	}
}
