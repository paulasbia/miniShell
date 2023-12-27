/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:20:58 by paula             #+#    #+#             */
/*   Updated: 2023/12/27 16:12:36 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("eh diferente\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_msg(t_env *mini)
{
	t_env	*aux;

	aux = mini;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(varname(aux->key), STDOUT_FILENO);
		if (ft_strchr(aux->key, '=')) // falta ainda incluir OLDPWD
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(varvalue(aux->key), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **my_env)
{
	int	exit_status;
	int	i;

	exit_status = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (export_msg(*my_env));
	while (args[i])
	{
		if (check_key(args[i]) == 0)
		{
			print_error_var("export", args[i]);
			exit_status = EXIT_FAILURE;
		}
		i++;
	}
	return (exit_status);
}
