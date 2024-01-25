/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/01/25 10:41:26 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_save_fds(int saved_fd[2])
{
	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
}

void	exit_child(t_dados *data, t_env *my_env)
{
	rl_clear_history();
	ft_free_env(&my_env);
	free_list(&data);
	close_all_fds();
	exit(EXIT_FAILURE);
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

void    ft_handle_pipes(int saved_fds_out, t_dados *data)
{
    
}

int	ft_execute_multiple_cmd(t_dados *data, t_env *my_env)
{
	int		saved_fds[2];
	int		status;
	pid_t	*children_pid;
	int		i;

	ft_save_fds(saved_fds);
	i = 0;
	while (data->next)
	{
        ft_handle_pipes(saved_fds[1], data);
		children_pid[i] = fork;
		ft_def_signal(children_pid[i]);
		if (children_pid[i] < 0)
			ft_child_err("fork", data->comando[0]);
		if (!children_pid[i])
		{
			ft_handle_red_pipes(data, my_env);
		}
	}
	return ();
}
