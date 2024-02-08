#include "../includes/minishell.h"

int	number_pipes(t_dados *temporary)
{
	int	i;

	i = 0;
	while (temporary) 
	{
		i++;
		temporary = temporary->next;
	}
	return(i);

}

int exec_testes(t_dados *data, t_env **my_env) 
{
	t_dados *temporary = data;
	int		nbr_pipes;

	nbr_pipes = number_pipes(temporary);
	(void)my_env;
	auto int pipes_fd[nbr_pipes][2];
	for (int x = 0; x < nbr_pipes; x++) {
		if (pipe(pipes_fd[x]) == -1) {
			perror("pipe");
			return -1;
		}
	}

	temporary = data;
	int pos = 0;
	while (temporary && pos < nbr_pipes) {
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			return -1;
		} else if (pid == 0) {  // Child process
			if (pos != 0) {
				dup2(pipes_fd[pos - 1][IN], STDIN_FILENO);
				close(pipes_fd[pos - 1][IN]);
			}
			if (pos != nbr_pipes - 1) {
				dup2(pipes_fd[pos][OUT], STDOUT_FILENO);
				close(pipes_fd[pos][OUT]);
			}

			// Close all pipe file descriptors in the child process
			for (int j = 0; j < nbr_pipes; j++) {
				close(pipes_fd[j][IN]);
				close(pipes_fd[j][OUT]);
			}

			if (execvp(temporary->comando[0], temporary->comando) == -1) {
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		} else { // Parent process
			pos++;
			temporary = temporary->next;
		}
	}

	// Close all pipe file descriptors in the parent process
	for (int x = 0; x < nbr_pipes; x++) {
		close(pipes_fd[x][IN]);
		close(pipes_fd[x][OUT]);
	}

	// Wait for all child processes to finish
	for (int j = 0; j < nbr_pipes; j++) {
		wait(NULL);
	}

	return 0;
}
