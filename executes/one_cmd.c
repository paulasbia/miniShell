/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:18:04 by paula             #+#    #+#             */
/*   Updated: 2023/12/21 11:41:06 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	one_cmd(char *input, t_env **my_env)
{
	char	**args;
	int		exit_status;

	args = ft_split(input, ' ');
	free(input);
	exit_status = execute_builtin(args, my_env);
	return (exit_status);
}
