/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:14:13 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:24:53 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
