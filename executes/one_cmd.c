/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 10:10:21 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// precisa criar outro comando
int	ft_one_cmd(char *input, t_env **my_env)
{
	char	**args;
	int		exit_status;

	args = ft_split(input, ' ');
	free(input);
	if (ft_cmd_builtin(args))
		exit_status = ft_execute_builtin(args, my_env);
	else
		exit_status = ft_execute_builtin(args, my_env);
	return (exit_status);
}
