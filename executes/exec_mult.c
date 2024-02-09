/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_red_pipes(t_dados *data, t_env *my_env)
{
	int	number_red;
	int	i;

	number_red = data->nbr_redirections;
	i = 0;
	while (number_red--)
	{
		if (data->redirect[i].redirect_type == 0
			|| data->redirect[i].redirect_type == 3)
		{
			if (!redirect_output(&data->redirect[i]))
				exit_child(data, my_env);
		}
		if (data->redirect[i].redirect_type == 1
			|| data->redirect[i].redirect_type == 2)
		{
			if (!redirect_input(&data->redirect[i]))
				exit_child(data, my_env);
		}
		i++;
	}
}

void	ft_handle_pipe(t_dados *aux, t_dados *data, int *saved_fds)
{
	int			back_out;
	static int	pipe_fd[2];

	back_out = saved_fds[OUT];
	if (aux != data)
		redirect_fd(pipe_fd[IN], STDIN_FILENO);
	if (aux->next)
	{
		if (pipe(pipe_fd) < 0)
			ft_child_err("pipe", aux->cmd[0]);
		redirect_fd(pipe_fd[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(back_out, STDOUT_FILENO);
}

void	ft_handle_exec(t_dados *aux, t_env *my_env)
{
	close_extra_fds();
	if (!ft_cmd_builtin(aux))
		ft_exec_child_process(aux, my_env);
	else
		exit(ft_execute_builtin(aux, &my_env));
}

void	check_child_pid(int child_pid, t_dados *data)
{
	if (child_pid < 0)
		ft_child_err("fork", data->cmd[0]);
}

int	ft_execute_multiple_cmd(t_dados *data, t_env *my_env)
{
	int		saved_fds[2];
	pid_t	*children_pid;
	int		i;
	t_dados	*aux;

	ft_save_fds(saved_fds);
	children_pid = ft_alloc(data);
	aux = data;
	i = 0;
	while (aux)
	{
		ft_handle_pipe(aux, data, saved_fds);
		children_pid[i] = fork();
		check_child_pid(children_pid[i], aux);
		ft_def_signal(children_pid[i]);
		if (!children_pid[i++])
		{
			ft_handle_red_pipes(aux, my_env);
			ft_handle_exec(aux, my_env);
		}
		aux = aux->next;
	}
	back_saved_fd(saved_fds);
	return (wait_for_children(children_pid));
}
