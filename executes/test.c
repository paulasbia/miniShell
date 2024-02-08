#include "../includes/minishell.h"

int exec_testes(t_dados *data, t_env **my_env) {
	t_dados *temporary = data;

	int i = 0;
	(void)my_env;
	while (temporary) {
		i++;
		temporary = temporary->next;
	}

	int pipes[i][2];
	for (int x = 0; x < i; x++) {
		if (pipe(pipes[x]) == -1) {
			perror("pipe");
			return -1;
		}
	}

	temporary = data;
	int pos = 0;
	while (temporary && pos < i) {
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			return -1;
		} else if (pid == 0) {  // Child process
			if (pos != 0) {
				dup2(pipes[pos - 1][IN], STDIN_FILENO);
				close(pipes[pos - 1][IN]);
			}
			if (pos != i - 1) {
				dup2(pipes[pos][OUT], STDOUT_FILENO);
				close(pipes[pos][OUT]);
			}

			// Close all pipe file descriptors in the child process
			for (int j = 0; j < i; j++) {
				close(pipes[j][IN]);
				close(pipes[j][OUT]);
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
	for (int x = 0; x < i; x++) {
		close(pipes[x][IN]);
		close(pipes[x][OUT]);
	}

	// Wait for all child processes to finish
	for (int j = 0; j < i; j++) {
		wait(NULL);
	}

	return 0;
}
