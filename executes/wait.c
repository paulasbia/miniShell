/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:57:39 by paula             #+#    #+#             */
/*   Updated: 2024/02/20 13:03:08 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_control_c(int status)
{
	return (WTERMSIG(status) == SIGINT);
}

static int	is_control_slash(int status)
{
	return (WTERMSIG(status) == SIGQUIT);
}

static int	handle_sig_int(int status, int is_last_child)
{
	if (is_control_c(status))
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (is_control_slash(status) && is_last_child)
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (INTERRUPT + WTERMSIG(status));
}

int	ft_wait_exit_status(int child_pid)
{
	int	status;

	if (child_pid == FORK_ERROR)
		return (EXIT_FAILURE);
	if (waitpid(child_pid, &status, 0) < 0)
		print_error_msg("waitpid", ft_itoa(child_pid));
	if (WIFSIGNALED(status))
		return (handle_sig_int(status, child_pid));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(t_child *children, int size_children)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < size_children)
	{
		exit_status = ft_wait_exit_status(children[i].pid);
		i++;
	}
	free(children);
	return (exit_status);
}
