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
	return(i);

}

void	ft_close_pipes(char *cmd, t_child *children, int nbr_pipes)
{
	int i;

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

int	exec_testes(t_dados *data, t_env **my_env)
{
	(void)my_env;
	t_child	*children;
	int	nbr_pipes;
	int	i;
	int	count;
	t_dados	*temp;

	nbr_pipes = data_counter(data) - 1;
	children = ft_alloc(data);
	i = 0;
	temp = data;
	while (i < nbr_pipes)
	{
		if (pipe(children[i].pfd) < 0)
			ft_child_err("pipe", data->cmd[0]);
		i++;
	}
	count = 0;
	// auto int count = 0;
	while (data)
	{
		children[count].pid = fork();
		ft_def_signal(children[count].pid);
		if (children[count].pid < 0)
			ft_child_err("fork", data->cmd[0]);
		if (children[count].pid == 0) //filho
		{
			if (count != 0) 
			{
				dup2(children[count - 1].pfd[READ_END], STDIN_FILENO);
				//close(children[count - 1].pfd[READ_END]);
			}
			if (count != nbr_pipes) 
			{
				dup2(children[count].pfd[WRITE_END], STDOUT_FILENO);
				//close(children[count].pfd[OUT]);
			}
			ft_close_pipes(data->cmd[0], children, nbr_pipes);
			ft_handle_red_pipes(data, *my_env);
			ft_handle_exec(data, *my_env);
		}
		// else // eh o pai
		// {
		// 	if (count < nbr_pipes)
		// 		close(children[count].pfd[WRITE_END]);				
		// 	if (count > 0)
		// 		close(children[count - 1].pfd[READ_END]);
		// }
		data = data->next;
		count++;
	}
	ft_close_pipes(temp->cmd[0], children, nbr_pipes);
	return(wait_for_children(children, nbr_pipes + 1));
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
