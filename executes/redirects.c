/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:17:22 by paula             #+#    #+#             */
/*   Updated: 2024/02/01 17:25:05 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_output(t_redirect *red)
{
	int	fd;
	int	open_flags;

	if (red->redirect_type == 3)
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (red->redirect_type == 0)
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(red->filename, open_flags, 0644);
	if (fd < 0)
	{
		ft_child_err("open", red->filename);
		return (0);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (1);
}

int	redirect_input(t_redirect *red)
{
	int	fd;

	fd = open(red->filename, O_RDONLY, 1);
	if (fd < 0)
	{
		ft_child_err("open", red->filename);
		return (0);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (1);
}

int	handle_red_intput(t_redirect *red, int saved_fd[2])
{
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	if (!redirect_input(red))
	{
		dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
		return (0);
	}
	return (1);
}

int	handle_red_output(t_redirect *red, int saved_fd[2])
{
	if (saved_fd[1] == -1)
		saved_fd[1] = dup(STDOUT_FILENO);
	if (!redirect_output(red))
	{
		dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
		return (0);
	}
	return (1);
}

// TODO refatorar, criar variavel para nbr e so passar
// os dados necessarios para out e in - OK
int	handle_redirects(t_dados *data, int saved_fd[2])
{
	int	number_red;
	int	i;

	i = 0;
	number_red = data->nbr_redirections;
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	while (number_red--)
	{
		if (data->redirect[i].redirect_type == 0
			|| data->redirect[i].redirect_type == 3)
		{
			if (!handle_red_output(&data->redirect[i], saved_fd))
				return (0);
		}
		if (data->redirect[i].redirect_type == 1
			|| data->redirect[i].redirect_type == 2)
		{
			if (!handle_red_intput(&data->redirect[i], saved_fd))
				return (0);
		}
		i++;
	}
	return (1);
}
