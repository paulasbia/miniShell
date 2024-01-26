/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/01/26 09:08:44 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_save_fds(int saved_fd[2])
{
	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
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

	ft_save_fds(saved_fds);
	i = 0;
	children_pid = ft_alloc(data);
	while (data)
	{
		ft_handle_pipes(saved_fds[1], data);
		children_pid[i] = fork();
		ft_def_signal(children_pid[i]);
		if (children_pid[i] < 0)
			ft_child_err("fork", data->comando[i]);
		if (!children_pid[i])
		{
			ft_handle_red_pipes(data, my_env);
		}
		data = data->next;
	}
    free(children_pid);
	return (0); // QUAL SINAL RETORNAR???
}
