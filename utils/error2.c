/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:48:59 by paula             #+#    #+#             */
/*   Updated: 2024/01/10 09:51:32 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_errors(char **args, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(args[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	ft_free_args(args);
	ft_free_args(envp);
	free(path);
	exit(error);
}
