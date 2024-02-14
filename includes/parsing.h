/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:34:54 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/14 11:07:20 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/////////////////// STRUCTS //////////////////

typedef struct s_env	t_env;

typedef struct s_redirect
{
	int					redirect_type;
	char				*filename;
}						t_redirect;

typedef struct s_dados
{
	int					nbr_redirections;
	char				**cmd;
	t_redirect			*redirect;
	struct s_dados		*next;
}						t_dados;

typedef struct s_int_parsing
{
	int					i;
	int					j;
	int					x;
	int					nbr_reds;
	int					nbr_cmd;
}						t_int_parsing;

//////////////////////////////////////////////
////////////////// PARSING ///////////////////
//////////////////////////////////////////////

////////////////// VALIDATE INPUT //////////// ok
int						validate_input(char *s);
int						invalid_token(char token, char *s, int *i);
int						invalid_quotes(char token, char *s, int *i);
int						invalid_pipe(char *s, int *i, int x);

////////////////// PARSING  ////////////////// ok
t_dados					*parsing(char *input, t_env *my_env, int exit_status);
void					handle_parsing_split(char *s_pipe, t_dados **dados_head,
							t_env *env, int exit);
t_dados					*ft_lstnew_p(char **split_cmd, t_env *env, int exit,
							t_dados *node);
t_dados					*alloc_nodes(int n_reds, int n_cmd);

////////////////// FREE PARSING ////////////// ok
void					free_dp(char **split);
void					free_list(t_dados **lst);

////////////////// CLEAN QUOTES //////////////

int						quotes_len(char *s);
void					handle_quotes(int *i, int *j, char *new_string,
							char *s);
char					*clean_quotes(char *s);
char					**clear_dp_quotes(char **split_cmd);
void					handle_clean_quotes(t_dados *node, char **split_cmd);

////////////////// COUNT SPLIT  //////////////
void					handle_count_ms(int *i, const char *s, int *result,
							char c);
void					handle_count_redirection(int *i, const char *s,
							int *result);
int						handle_count_loop(char const *s, int result, int *i);
int						count_split_ms(char const *s);

////////////////// SPLIT MS ////////////////// ok
char					**split_ms(char const *s);
char					*count_word(char const *s, int *i);
char					*handle_both_quotes(char const *s, int *i, int *index,
							int *j);
char					*handle_tokens(char const *s, int *i, int *j,
							int *index);
char					*alloc_word(const char *s, int j, int index);

////////////////// SPLIT PIPE  /////////////// ok
char					**split_pipe(char const *s);
char					*cont_word_pipe(char const *s, int *i);
void					handle_quotes_on_pipe(int *i, int *j, char const *s,
							char c);
char					*alloc_word_p(const char *s, int j, int index);
int						cont_pipe(char const *s);

////////////////// UTILS PARSING ///////////// ok
int						redirection(char *red);
void					ms_lstadd_back(t_dados **lst, t_dados *node);
// void					print_list(t_dados *lst);

////////////////// EXPANSION  //////////////// ok
int						handle_exit_status(char **command, int j,
							int exit_status);
int						handle_command(int *j, char **cmd, t_env *tmp_l_env,
							t_dados *n);
int						command_expansion(t_dados *n, char **cmd,
							t_env *tmp_l_env, int exit_status);
int						expansion(t_dados *n, t_env *env, int exit_status);

////////////////// EXPAN CHANGES /////////////
void					move_empty_command(char **cmd, int i);
int						is_space(char c);
char					*change_input(char **cmd_input, char *key,
							int size_index_env);
char					*change_exit(char *cmd_input, char *string_exit,
							int size);
void					change_wrong_env(char **command, char *env_input,
							char *replace, int j);

////////////////// EXPAN UTILS ///////////////
int						val_chars_env(char c);
int						find_char(char *s, char c);
int						find_exception(char *cmd_input, int j);
void					check_expansion_quotes(char *command, int *j);
t_env					*search_env(char **command, t_env *tmp_env,
							char *env_input);

////////////////// EXPAN FILENAME ////////////
int	command_expansion_filename(char **file, t_env *tmp_l_env,
		int exit_status);


#endif
