/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:33 by paula             #+#    #+#             */
/*   Updated: 2024/02/01 09:43:50 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/parsing.h" // parsing
# include "../libft/libft.h"      // libft
# include <fcntl.h>               // open flags
# include <readline/history.h>    // history
# include <readline/readline.h>   // readline
# include <signal.h>              // sigaction
# include <stdio.h>               // perror
# include <stdlib.h>              // getenv
# include <sys/stat.h>            // stat
# include <sys/wait.h>            // waitpid
# include <unistd.h>              // getpwd

# define IN 0
# define OUT 1
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

int					ft_check_arg(int ac, char **av);
int					minishell(t_env *my_env);
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
pid_t				*ft_alloc(t_dados *data);
int					ft_get_exit_status(int status);
void				redirect_fd(int fd_for_red, int fd_local);
void				ft_save_fds(int saved_fd[2]);

// EXECUTES
int					start_execution(t_dados *data, t_env **my_env);
t_dados				*parse_heredoc(t_dados *dados);
int					ft_one_cmd(t_dados *data, t_env **my_env);
int					ft_execute_child(t_dados *data, t_env *my_env);
int					ft_execute_builtin(t_dados *data, t_env **minienv);
int					ft_exec_child_process(char **args, t_env *my_env);
int					ft_execute_multiple_cmd(t_dados *data, t_env *my_env);

// wait
int					wait_for_children(int *children_pid);
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
void				ft_handle_errors(char **args, char *path, char **envp);
void				print_error_msg2(char *msg, char command);

#endif