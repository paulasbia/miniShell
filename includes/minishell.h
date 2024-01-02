/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:33 by paula             #+#    #+#             */
/*   Updated: 2024/01/02 11:28:08 by paula            ###   ########.fr       */
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

// builtins
int					ft_execute_builtin(char **args, t_env **minienv);
int					ft_cmd_builtin(char **args);
int					ft_pwd(void);
int					ft_exit(char **arg, t_env **my_env);
int					ft_echo(char **args);
int					ft_env(t_env *my_env);
int					ft_unset(char **args, t_env **minienv);
int					ft_export(char **args, t_env **my_env);
char				*ft_varname(char *name);
char				*ft_varvalue(char *value);
int					ft_cd(char **args, t_env *my_env);

// prompt
char				*ft_get_prompt(void);

// signals
void				ft_init_signal(void);

// frees
void				ft_free_env(t_env **my_env);

// error
void				print_error_msg(char *command, char *msg);
void				ft_print_error_var(char *command, char *var);
void				ft_exit_with_error(char *command, char *msg, int error);
int					ft_cd_err_msg(char *err_msg);

// EXECUTES
int					ft_one_cmd(char *input, t_env **my_env);
#endif