/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:20:58 by paula             #+#    #+#             */
/*   Updated: 2023/12/27 11:34:06 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_error_msg(t_env *mini)
{
	t_env	*aux;

	aux = mini;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(varname(aux->key), STDOUT_FILENO);
		if (ft_strchr(aux->key, '=')) //falta ainda incluir OLDPWD
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(varvalue(aux->key), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
}

int	ft_export(char **args, t_env **my_env)
{
	if (!args[1])
		export_error_msg(*my_env);
	return (0);
}
