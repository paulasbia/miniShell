/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:48:59 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 18:53:51 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_errors(t_dados *data, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(data->comando[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free_list(&data);
	ft_free_args(envp);
	if (path)
		free(path);
	exit(error);
}

void	print_error_msg2(char *msg, char command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd(command, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
