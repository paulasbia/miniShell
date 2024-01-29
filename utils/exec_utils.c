/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:06:44 by paula             #+#    #+#             */
/*   Updated: 2024/01/29 11:54:01 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_child(t_dados *data, t_env *my_env)
{
	rl_clear_history();
	ft_free_env(&my_env);
	free_list(&data);
	exit(EXIT_FAILURE);
}

pid_t	*ft_alloc(t_dados *data)
{
	int	i;

	i = 0;
	while (data)
	{
		i++;
		data = data->next;
	}
	return (malloc(sizeof(pid_t) * (i + 1)));
}

void	ft_save_fds(int saved_fd[2])
{
	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
}

void	redirect_fd(int fd_for_red, int fd_local)
{
	dup2(fd_for_red, fd_local);
	close(fd_for_red);
}
