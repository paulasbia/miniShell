/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:57:39 by paula             #+#    #+#             */
/*   Updated: 2024/01/29 10:57:59 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wait_exit_status(int child_pid)
{
	int	status;

	if (child_pid == FORK_ERROR)
		return (EXIT_FAILURE);
	if (waitpid(child_pid, &status, 0) < 0)
		print_error_msg("waitpid", ft_itoa(child_pid));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(int *children_pid)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (children_pid[i])
	{
		exit_status = ft_wait_exit_status(children_pid[i]);
		i++;
	}
	free(children_pid);
	return (exit_status);
}
