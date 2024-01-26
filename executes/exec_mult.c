/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/01/26 11:19:27 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (aux != data)
			redirect_fd(saved_fds[IN], STDIN_FILENO);
		if (aux->next)
		{
			if (pipe(saved_fds) < 0)
				ft_child_err("pipe", aux->comando[i]);
			redirect_fd(saved_fds[OUT], STDOUT_FILENO);
		}
		else
			redirect_fd(back_out, STDOUT_FILENO);
		children_pid[i] = fork();
		ft_def_signal(children_pid[i]);
		if (children_pid[i] < 0)
			ft_child_err("fork", aux->comando[i]);
		if (!children_pid[i])
		{
			ft_handle_red_pipes(aux, my_env);
            ft_exec_child_process(aux->comando, my_env);
		}
		aux = aux->next;
        i++;
	}
	free(children_pid);
	back_saved_fd(saved_fds);
	return (0); // QUAL SINAL RETORNAR???
}
