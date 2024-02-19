/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:43:52 by paula             #+#    #+#             */
/*   Updated: 2024/02/19 10:03:41 by paula            ###   ########.fr       */
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
		if (data->redirect[i].ambiguos == 1)
			ft_handle_errors2(data, data->redirect[i].filename);
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

int	ft_handle_exec(t_dados *aux, t_env *my_env, int nbr_pipes)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_cmd_builtin(aux))
		ft_exec_child_process(aux, my_env);
	else if (!nbr_pipes)
		exit_status = ft_execute_builtin(aux, &my_env);
	else
	{
		exit_status = ft_execute_builtin(aux, &my_env);
		close_all();
		exit(exit_status);
	}
	return (exit_status);
}

int	check_return(t_exec ex, t_dados *temp, t_child *children)
{
	(void)temp;
	if (ex.nbr_pipes > 0)
		return (wait_for_children(children, ex.nbr_pipes + 1));
	else
	{
		free(children);
		return (ex.i);
	}
}

void	exec_cmd_pipes(t_child *children, t_exec ex, t_dados *data,
		t_env **my_env)
{
	do_dup(children, ex.count, ex.nbr_pipes, data);
	ft_handle_red_pipes(data, *my_env);
	ex.i = ft_handle_exec(data, *my_env, ex.nbr_pipes);
}

int	start_execution(t_dados *data, t_env **my_env)
{
	t_child	*children;
	t_exec	ex;
	t_dados	*temp;

	init_ex(&ex, data);
	children = ft_alloc(data);
	temp = data;
	create_pipes(ex.nbr_pipes, children, data);
	if (ex.nbr_pipes == 0)
		ex.i = ft_one_cmd(data, my_env);
	else
	{
		while (data)
		{
			create_fork(ex.nbr_pipes, children, data, ex.count);
			if (children[ex.count].pid == 0)
				exec_cmd_pipes(children, ex, data, my_env);
			data = data->next;
			ex.count++;
		}
	}
	ft_close_pipes(temp->cmd[0], children, ex.nbr_pipes);
	return (check_return(ex, temp, children));
}
