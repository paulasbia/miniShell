/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:20:58 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 16:03:44 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_entry_exist(char *var, t_env *my_env)
{
	t_env	*aux;

	aux = my_env;
	while (aux)
	{
		if (!ft_strncmp(aux->key, var, ft_strlen(var)))
		{
			if (aux->key[ft_strlen(var)] == '=')
				return (1);
		}
		aux = aux->next;
	}
	return (0);
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//falta ainda incluir OLDPWD. DUVIDA: precisa ser na ordem alfabetica?
int	export_msg(t_env *mini)
{
	t_env	*aux;

	aux = mini;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(ft_varname(aux->key), STDOUT_FILENO);
		if (ft_strchr(aux->key, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(ft_varvalue(aux->key), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **my_env)
{
	int		exit_status;
	int		i;
	char	*name_var;

	exit_status = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (export_msg(*my_env));
	while (args[i])
	{
		name_var = ft_varname(args[i]);
		printf("aqui args[i] eh %s\n", args[i]);
		if (check_key(args[i]) == 0)
		{
			ft_print_error_var("export", args[i]);
			exit_status = EXIT_FAILURE;
		}
		else if (ft_env_entry_exist(name_var, *my_env))
			ft_update_envlist(name_var, ft_varvalue(args[i]), *my_env);			
		else
			ft_add_list(args[i], my_env);
		i++;
	}
	return (exit_status);
}
