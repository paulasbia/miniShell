/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:20:58 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
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

// falta ainda incluir OLDPWD. DUVIDA: precisa ser na ordem alfabetica?
int	export_msg(t_env *mini)
{
	t_env	*aux;
	char	*name_var;

	aux = mini;
	while (aux)
	{
		name_var = ft_varname(aux->key);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_var, STDOUT_FILENO);
		if (ft_strchr(aux->key, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(ft_varvalue(aux->key), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
		free(name_var);
	}
	return (0);
}

// temos que lidar com as "" pois a entrada deve conter elas
// mas ignorar ao printar.
int	ft_export(t_dados *data, t_env **my_env)
{
	int		exit_status;
	int		i;
	char	*name_var;

	exit_status = EXIT_SUCCESS;
	i = 1;
	if (!data->cmd[i])
		return (export_msg(*my_env));
	while (data->cmd[i])
	{
		name_var = ft_varname(data->cmd[i]);
		if (check_key(name_var) == 0)
		{
			ft_print_error_var("export", data->cmd[i]);
			exit_status = EXIT_FAILURE;
		}
		else if (ft_env_entry_exist(name_var, *my_env))
			ft_update_envlist(name_var, ft_varvalue(data->cmd[i]), *my_env);
		else
			ft_add_list(data->cmd[i], my_env);
		i++;
		free(name_var);
	}
	return (exit_status);
}
