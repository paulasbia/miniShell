/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:06:44 by paula             #+#    #+#             */
/*   Updated: 2024/01/30 19:26:25 by paula            ###   ########.fr       */
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

//um malloc, como proteger?
pid_t	*ft_alloc(t_dados *data)
{
	int		i;
	pid_t	*alloc;

	i = 0;
	while (data)
	{
		i++;
		data = data->next;
	}
	alloc = malloc(sizeof(pid_t) * (i + 1));
	if (alloc == NULL)
		print_error_msg("alloc", "malloc fail");
	alloc[i] = 0;
	return (alloc);
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
