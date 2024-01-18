/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:17:22 by paula             #+#    #+#             */
/*   Updated: 2024/01/18 11:00:15 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_output(t_dados *data)
{
	int	fd;
	int	open_flags;

	if (data->redirect->redirect_type == 0)
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (data->redirect->redirect_type == 3)
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(data->redirect->filename, open_flags, 0644);
	if (fd < 0)
	{
		ft_child_err("open", data->redirect->filename);
		return (0);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (1);
}

int	handle_red_output(t_dados *data, int saved_fd[2])
{
	if (saved_fd[1] == -1)
		saved_fd[1] = dup(STDOUT_FILENO);
	if (!redirect_output(data))
	{
		dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
		return (0);
	}
	return (1);
}

int	handle_redirects(t_dados *data, int saved_fd[2])
{
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	while (data->nbr_redirections)
	{
		if (data->redirect->redirect_type == 0
			|| data->redirect->redirect_type == 3)
		{
			if (!handle_red_output(data, saved_fd))
				return (0);
		}
		data->nbr_redirections--;
	}
	return (1);
}
