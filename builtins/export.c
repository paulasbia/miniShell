/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:20:58 by paula             #+#    #+#             */
/*   Updated: 2023/12/27 15:20:09 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    int i;

	exit_status = EXIT_SUCCESS;
    i = 1;
	if (!args[i])
		return (export_msg(*my_env));
	return (exit_status);
}
