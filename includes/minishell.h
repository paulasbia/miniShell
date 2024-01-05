/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:33 by paula             #+#    #+#             */
/*   Updated: 2024/01/05 10:57:04 by ricardo          ###   ########.fr       */
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

int					check_arg(int ac, char **av);
int					minishell(t_env *my_env);

// builtins
int					execute_builtin(char **args, t_env **minienv);
int					cmd_builtin(char **args);
int					pwd(void);
int					ft_exit(char **arg, t_env **my_env);
int					echo(char **args);
int					env(t_env *my_env);
int					unset(char **args, t_env **minienv);
int					ft_export(char **args, t_env **my_env);
char				*varname(char *name);
char				*varvalue(char *value);

// prompt
char				*get_prompt(void);

// signals
void				init_signal(void);

// frees
void				free_env(t_env **my_env);

// error
void				print_error_var(char *command, char *var);
void				exit_with_error(char *command, char *msg, int error);

// EXECUTES
int					one_cmd(char *input, t_env **my_env);



#endif