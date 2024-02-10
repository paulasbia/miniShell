/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:33 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:07:34 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/parsing.h" // parsing
# include "../libft/libft.h"      // libft
# include <fcntl.h>               // open flags
# include <limits.h>              //llong int
# include <readline/history.h>    // history
# include <readline/readline.h>   // readline
# include <signal.h>              // sigaction
# include <stdio.h>               // perror
# include <stdlib.h>              // getenv
# include <sys/stat.h>            // stat
# include <sys/wait.h>            // waitpid
# include <unistd.h>              // getpwd

//# define LLONG_MAX 9223372036854775807
# define READ_END 0
# define WRITE_END 1
# define PATH_MAX 4096
# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG "command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"
# define GRN "\001\e[0;32m\002"
# define MAG "\001\e[0;35m\002"
# define CRESET "\001\e[0m\002"
# define PROMPT "minishell_by_pde-souz_and_tbolzan-: "

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
}					t_env;

struct				s_parse_heredoc
{
	int				i;
	pid_t			child_pid;
	t_redirect		*red_temp;
};

typedef struct s_children
{
	pid_t			pid;
	int				pfd[2];
}					t_child;

typedef struct s_exec
{
	int	i;
	int	count;
	int	nbr_pipes;
}					t_exec;

int	data_counter(t_dados *temp);
void	create_pipes(int nbr_pipes, t_child *children, t_dados *data);
void	check_child_pid(int child_pid, t_dados *data);
void	create_fork(int nbr_pipes, t_child *children, t_dados *data, int count);
void	do_dup(t_child *children, int count, int nbr_pipes, t_dados *data);
void	ft_close_pipes(char *cmd, t_child *children, int nbr_pipes);


int					exec_testes(t_dados *data, t_env **my_env);
void				ft_handle_red_pipes(t_dados *data, t_env *my_env);
int					ft_handle_exec(t_dados *aux, t_env *my_env, int nbr_pipes);

int					ft_check_arg(int ac, char **av);
int					minishell(t_env *my_env, int exit_status);
void				ft_add_list(char *key, t_env **my_list);

// env
t_env				*init_minienv(char **env);
void				ft_add_list(char *key, t_env **my_list);
void				ft_update_envlist(char *name, char *value, t_env *my_env);
t_env				*ft_seach_node(char *name, t_env *my_env);
char				*mini_value(char *name, t_env *my_env);
size_t				minienv_size(t_env *my_env);
char				**myenv_to_array(t_env *my_env);

// utils
int					ft_cmd_builtin(t_dados *data);
int					str_equal(const char *str1, const char *str2);
void				exit_child(t_dados *data, t_env *my_env);
t_child				*ft_alloc(t_dados *data);
int					ft_get_exit_status(int status);
void				redirect_fd(int fd_for_red, int fd_local);
void				ft_save_fds(int saved_fd[2]);
void				close_extra_fds(void);

// EXECUTES
int					start_execution(t_dados *data, t_env **my_env);
void				parse_heredoc(t_dados *dados);
int					ft_one_cmd(t_dados *data, t_env **my_env);
int					ft_execute_child(t_dados *data, t_env *my_env);
int					ft_execute_builtin(t_dados *data, t_env **minienv);
int					ft_exec_child_process(t_dados *data, t_env *my_env);
int					ft_execute_multiple_cmd(t_dados *data, t_env *my_env);

// wait
int					wait_for_children(t_child *children, int size_children);
int					ft_wait_exit_status(int child_pid);

// redirects
int					handle_redirects(t_dados *data, int saved_fd[2]);
void				back_saved_fd(int saved_fd[2]);
int					redirect_output(t_redirect *red);
int					redirect_input(t_redirect *red);

// builtins
int					ft_pwd(void);
int					ft_exit(t_dados *data, t_env **my_env);
int					ft_echo(t_dados *data);
int					ft_env(t_env *my_env);
int					ft_unset(t_dados *data, t_env **my_env);
int					ft_export(t_dados *data, t_env **my_env);
char				*ft_varname(char *name);
char				*ft_varvalue(char *value);
int					ft_cd(t_dados *data, t_env **my_env);

// prompt
char				*ft_get_prompt(void);

// signals
void				ft_init_signal(void);
void				ft_def_signal(pid_t child_pid);

// frees
void				ft_free_env(t_env **my_env);
void				ft_free_args(char **args);
void				ft_clean(char **to_clean);

// error
void				print_error_msg(char *command, char *msg);
void				ft_print_error_var(char *command, char *var);
void				ft_exit_with_error(char *command, char *msg, int error);
int					ft_cd_err_msg(char *err_msg);
void				ft_child_err(char *cmd, char *msg);
void				ft_handle_errors(t_dados *data, char *path, char **envp);
void				print_error_msg2(char *msg, char command);

#endif