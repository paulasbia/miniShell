/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:33 by paula             #+#    #+#             */
/*   Updated: 2024/01/09 09:18:21 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"    // libft
# include <fcntl.h>             // open flags
# include <readline/history.h>  // history
# include <readline/readline.h> // readline
# include <signal.h>            // sigaction
# include <stdio.h>             // perror
# include <stdlib.h>            // getenv
# include <sys/stat.h>          // stat
# include <sys/wait.h>          // waitpid
# include <unistd.h>            // getpwd

# define PATH_MAX 4096
# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"
# define GRN "\001\e[0;32m\002"
# define MAG "\001\e[0;35m\002"
# define CRESET "\001\e[0m\002"
# define PROMPT "minishell_by_pde-souz: "

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
}					t_env;

int					ft_check_arg(int ac, char **av);
int					minishell(t_env *my_env);
void				ft_add_list(char *key, t_env **my_list);

// env
void				ft_update_envlist(char *name, char *value, t_env *my_env);
t_env				*ft_seach_node(char *name, t_env *my_env);
char				*mini_value(char *name, t_env *my_env);
size_t				minienv_size(t_env *my_env);
char				**myenv_to_array(t_env *my_env);

// utils
int					ft_cmd_builtin(char **args);
int					str_equal(const char *str1, const char *str2);

// EXECUTES
int					ft_one_cmd(char *input, t_env **my_env);
int					ft_execute_builtin(char **args, t_env **minienv);
int					ft_exec_child_process(char **args, t_env *my_env);

// builtins
int					ft_pwd(void);
int					ft_exit(char **arg, t_env **my_env);
int					ft_echo(char **args);
int					ft_env(t_env *my_env);
int					ft_unset(char **args, t_env **minienv);
int					ft_export(char **args, t_env **my_env);
char				*ft_varname(char *name);
char				*ft_varvalue(char *value);
int					ft_cd(char **args, t_env **my_env);

// prompt
char				*ft_get_prompt(void);

// signals
void				ft_init_signal(void);
void				ft_def_signal(pid_t child_pid);

// frees
void				ft_free_env(t_env **my_env);
void				ft_free_args(char **args);

// error
void				print_error_msg(char *command, char *msg);
void				ft_print_error_var(char *command, char *var);
void				ft_exit_with_error(char *command, char *msg, int error);
int					ft_cd_err_msg(char *err_msg);
void				ft_child_err(char *cmd, char *msg);

#endif