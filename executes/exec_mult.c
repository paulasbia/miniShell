/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/01/26 11:43:36 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_for_children(int *children_pid)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		waitpid(children_pid[i], &exit_status, 0);
		exit_status = ft_get_exit_status(children_pid[i]);
		i++;
	}
    free(children_pid);
	return (exit_status);
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

void	ft_handle_red_pipes(t_dados *data, t_env *my_env)
{
	int	number_red;
	int	i;

	number_red = data->nbr_redirections;
	i = 0;
	while (number_red)
	{
		if (data->redirect[i].redirect_type == 0
			|| data->redirect[i].redirect_type == 3)
		{
			if (!redirect_output(&data->redirect[i]))
				exit_child(data, my_env);
		}
		if (data->redirect[i].redirect_type == 1)
		{
			if (!redirect_input(&data->redirect[i]))
				exit_child(data, my_env);
		}
		number_red--;
		i++;
	}
}

void	handle_fd_pipe(t_dados *data, t_dados *aux, int back_out)
{
	static int	fd_pipe[2];

	if (aux != data)
		redirect_fd(fd_pipe[IN], STDIN_FILENO);
	if (aux->next)
	{
		if (pipe(fd_pipe) < 0)
			ft_child_err("pipe", aux->comando[0]);
		redirect_fd(fd_pipe[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(back_out, STDOUT_FILENO);
}

int	ft_execute_multiple_cmd(t_dados *data, t_env *my_env)
{
	int		saved_fds[2];
	pid_t	*children_pid;
	int		i;
	t_dados	*aux;
	int		back_out;

	ft_save_fds(saved_fds);
	back_out = saved_fds[1];
	children_pid = ft_alloc(data);
	aux = data;
	i = 0;
	while (aux)
	{
		handle_fd_pipe(data, aux, back_out);
		children_pid[i] = fork();
		ft_def_signal(children_pid[i]);
		if (children_pid[i] < 0)
			ft_child_err("fork", aux->comando[0]);
		if (!children_pid[i])
		{
			ft_handle_red_pipes(aux, my_env);
			ft_exec_child_process(aux->comando, my_env);
		}
		aux = aux->next;
		i++;
	}
	back_saved_fd(saved_fds);
	return (wait_for_children(children_pid)); // QUAL SINAL RETORNAR???
}
