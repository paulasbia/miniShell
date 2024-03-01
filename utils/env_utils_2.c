/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:16:44 by paula             #+#    #+#             */
/*   Updated: 2024/03/01 13:40:47 by paula            ###   ########.fr       */
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

// um malloc, como proteger?
char	**myenv_to_array(t_env *my_env)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(my_env) + 1));
	if (envp == NULL)
		print_error_msg(*envp, "malloc fail");
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

void	ft_update_shlvl(char *value_sh, t_env *my_env)
{
	int	new_value;

	value_sh = mini_value("SHLVL", my_env);
	if (!value_sh)
	{
		ft_add_list("SHLVL=1", &my_env);
		return ;
	}
	new_value = ft_atoi(value_sh);
	new_value++;
	ft_update_envlist("SHLVL", ft_itoa(new_value), my_env);
}
