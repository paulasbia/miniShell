/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:34:54 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 15:29:09 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/////////////////// STRUCTS 

typedef struct s_env	t_env;

typedef struct s_redirect
{
	int					redirect_type;
	char				*filename;
}						t_redirect;

typedef struct s_dados
{
	int					nbr_redirections;
	char				**comando;
	t_redirect			*redirect;
	struct s_dados		*next;
}						t_dados;

typedef struct s_int_parsing
{
	int	i;
	int	j;
	int	x;
	int	nbr_reds;
	int	nbr_cmd;
}	t_int_parsing;

///////////////////// PARSING

t_dados					*parsing(char *input, t_env *my_env, int exit_status);
char					**split_ms(char const *s);
char					**split_pipe(char const *s);
int						validate_input(char *s);
char					*clean_quotes(char *s);
void					free_dp(char **split);
void					free_list(t_dados **lst);
int						count_split_ms(char const *s);
void					handle_clean_quotes(t_dados *node, char **split_cmd);
int						expansion(t_dados *node, t_env *env, int exit_status);
int						val_chars_env(char c);
int						find_char(char *s, char c);
int						find_exception(char *cmd_input, int j);
void					move_empty_command(char **comando, int i);
t_env					*search_env(char **command, t_env *tmp_env, char *env_input);
char					*change_input(char **cmd_input, char *key, int size_index_env);
int						redirection(char *red);
void					ms_lstadd_back(t_dados **lst, t_dados *node);
int						handle_exit_status(char **command, int j, int exit_status);
char					*change_exit(char *cmd_input, char *string_exit, int size);
void					change_wrong_env(char **command, char *env_input, char *replace, int j);
void					check_expansion_quotes(char *command, int *j);
int 					is_space(char c);

#endif
