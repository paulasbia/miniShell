/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:48:59 by paula             #+#    #+#             */
/*   Updated: 2024/02/20 16:13:02 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_errors(t_dados *data, char *path, char **envp)
{
	int	error;

	error = EXIT_FAILURE;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(data->cmd[0]);
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

void	ft_handle_errors2(t_dados *data, char *filename)
{
	print_error_msg(filename, "ambiguous redirect");
	free_list(&data);
	exit(EXIT_FAILURE);
}

void	print_error_msg2(char *msg, char command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd(command, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	print_error_msg3(char *command, char *msg)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}
