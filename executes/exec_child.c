/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:23 by paula             #+#    #+#             */
/*   Updated: 2024/01/03 16:31:24 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char    *ft_get_path(char *cmd, t_env *my_env)
// {
//     char    *path_env;
//     char    **paths;
// }

int	ft_exec_child_process(char **args, t_env *my_env)
{
	// char    *path;
	(void)my_env;
	// path = ft_get_path(args[0], my_env);
    execv("/usr/bin/ls", args);
	return (EXIT_SUCCESS);
}
