/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:06:44 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:28:21 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//um malloc, como proteger?
t_child	*ft_alloc(t_dados *data)
{
	int		i;
	t_child	*alloc;

	i = 0;
	while (data)
	{
		i++;
		data = data->next;
	}
	alloc = malloc(sizeof(t_child) * (i));
	if (alloc == NULL)
		print_error_msg("alloc", "malloc fail");
	return (alloc);
}

void	create_pipes(int nbr_pipes, t_child *children, t_dados *data)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe(children[i].pfd) < 0)
			ft_child_err("pipe", data->cmd[0]);
		i++;
	}
}

void	check_child_pid(int child_pid, t_dados *data)
{
	if (child_pid < 0)
		ft_child_err("fork", data->cmd[0]);
}

void	create_fork(int nbr_pipes, t_child *children, t_dados *data, int count)
{
	if (nbr_pipes > 0 || !ft_cmd_builtin(data))
		children[count].pid = fork();
	else
		children[count].pid = 0;
	ft_def_signal(children[count].pid);
	check_child_pid(children->pid, data);
}

void	do_dup(t_child *children, int count, int nbr_pipes, t_dados *data)
{
	if (count != 0)
		dup2(children[count - 1].pfd[READ_END], STDIN_FILENO);
	if (count != nbr_pipes)
		dup2(children[count].pfd[WRITE_END], STDOUT_FILENO);
	ft_close_pipes(data->cmd[0], children, nbr_pipes);
}

// void	ft_save_fds(int saved_fd[2])
// {
// 	saved_fd[0] = dup(STDIN_FILENO);
// 	saved_fd[1] = dup(STDOUT_FILENO);
// }

// void	redirect_fd(int fd_for_red, int fd_local)
// {
// 	dup2(fd_for_red, fd_local);
// 	close(fd_for_red);
// }
