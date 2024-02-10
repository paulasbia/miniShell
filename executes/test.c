/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:14:13 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:00:32 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	data_counter(t_dados *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_close_pipes(char *cmd, t_child *children, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (close(children[i].pfd[READ_END]) == -1)
			ft_child_err(cmd, "close READ_END");
		if (close(children[i].pfd[WRITE_END]) == -1)
			ft_child_err(cmd, "close WRITE_END");
		i++;
	}
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

void	init_ex(t_exec *ex, t_dados *data)
{
	ex->count = 0;
	ex->i = 0;
	ex->nbr_pipes = data_counter(data) - 1;
}

int	check_return(t_exec ex, t_dados *temp, t_child *children)
{
	if (ex.nbr_pipes > 0 || !ft_cmd_builtin(temp))
		return (wait_for_children(children, ex.nbr_pipes + 1));
	else
	{
		free(children);
		return (ex.i);
	}
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
	while (data)
	{
		create_fork(ex.nbr_pipes, children, data, ex.count);
		if (children[ex.count].pid == 0)
		{
			do_dup(children, ex.count, ex.nbr_pipes, data);
			ft_handle_red_pipes(data, *my_env);
			ex.i = ft_handle_exec(data, *my_env, ex.nbr_pipes);
		}
		data = data->next;
		ex.count++;
	}
	ft_close_pipes(temp->cmd[0], children, ex.nbr_pipes);
	return(check_return(ex, temp, children));
}

// int exec_testes(t_dados *data, t_env **my_env)
// {
// 	t_dados *temp;
// 	int		nbr_pipes;
// 	pid_t	child_pid;
// 	int		x;

// 	temp = data;
// 	nbr_pipes = number_pipes(temp);
// 	(void)my_env;
// 	auto int pipes_fd[nbr_pipes][2];
// 	x = 0;
// 	while (x < nbr_pipes)
// 	{
// 		if (pipe(pipes_fd[x]) == -1)
// 			ft_child_err("pipe", temp->comando[0]);
// 		x++;
// 	}
// 	auto int count = 0;
// 	auto int j = 0;
// 	while (temp && count < nbr_pipes)
// 	{
// 		child_pid = fork();
// 		ft_def_signal(child_pid);
// 		if (child_pid == -1)
// 			ft_child_err("fork", temp->comando[0]);
// 		else if (child_pid == 0) // Child process
// 		{
// 			if (count != 0) {
// 				dup2(pipes_fd[count - 1][IN], STDIN_FILENO);
// 				close(pipes_fd[count - 1][IN]);
// 			}
// 			if (count != nbr_pipes - 1) {

// 				dup2(pipes_fd[count][OUT], STDOUT_FILENO);
// 				close(pipes_fd[count][OUT]);
// 			}
// 			// Close all pipe file descriptors in the child process
// 			while (j < nbr_pipes)
// 			{
// 				close(pipes_fd[j][IN]);
// 				close(pipes_fd[j][OUT]);
// 				j++;
// 			}
// 			// ft_handle_red_pipes(temp, *my_env);
// 			// ft_handle_exec(temp, *my_env);
// 			if (execvp(temp->comando[0], temp->comando) == -1) {
// 				perror("execvp");
// 				exit(EXIT_FAILURE);
// 			}
// 		} else { // Parent process
// 			count++;
// 			temp = temp->next;
// 		}
// 	}

// 	// Close all pipe file descriptors in the parent process
// 	for (int x = 0; x < nbr_pipes; x++) {
// 		close(pipes_fd[x][IN]);
// 		close(pipes_fd[x][OUT]);
// 	}

// 	// Wait for all child processes to finish
// 	for (int j = 0; j < nbr_pipes; j++) {
// 		wait(NULL);
// 	}
// 	return (EXIT_SUCCESS);
// }
