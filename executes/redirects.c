/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:17:22 by paula             #+#    #+#             */
/*   Updated: 2024/02/20 16:28:59 by paula            ###   ########.fr       */
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
		ft_child_err(red->filename);
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
		ft_child_err(red->filename);
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

int	handle_redirects(t_dados *data, int saved_fd[2])
{
	t_int_parsing	n;

	n.i = 0;
	n.nbr_reds = data->nbr_redirections;
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	while (n.nbr_reds--)
	{
		n.x = data->redirect[n.i].redirect_type;
		if (data->redirect[n.i].ambiguos == 1)
			return (print_error_msg(data->redirect[n.i].filename,
					"ambiguous redirect"));
		if (n.x == 0 || n.x == 3)
		{
			if (!handle_red_output(&data->redirect[n.i], saved_fd))
				return (0);
		}
		if (n.x == 1 || n.x == 2)
		{
			if (!handle_red_intput(&data->redirect[n.i], saved_fd))
				return (0);
		}
		n.i++; 
	}
	return (1);
}
