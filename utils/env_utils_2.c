/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:16:44 by paula             #+#    #+#             */
/*   Updated: 2024/01/29 13:12:31 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	minienv_size(t_env *my_env)
{
	int	i;

	if (!my_env)
	{
		return (0);
	}
	i = 0;
	while (my_env != 0)
	{
		i++;
		my_env = my_env->next;
	}
	return (i);
}

//um malloc, como proteger?
char	**myenv_to_array(t_env *my_env)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(my_env) + 1));
	aux = my_env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->key);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
