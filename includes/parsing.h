/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:34:54 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/05 11:33:51 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_env t_env;

typedef struct s_redirect
{
	int				redirect_type;
	char			*filename;
}					t_redirect;

typedef struct s_dados
{
	int				nbr_redirections;
	char			**comando;
	t_redirect		*redirect;
	struct s_dados	*next;
}					t_dados;

// PARSING
t_dados				*parsing(char *input, t_env *my_env);
char				**split_ms(char const *s);
char				**split_pipe(char const *s);
int					validate_input(char *s);
char				*clean_quotes(char *s);
void				free_dp(char **split);
void				free_list(t_dados **lst);
int					count_split_ms(char const *s);
void				handle_clean_quotes(t_dados *node, char **split_cmd);
int				expansion(t_dados *node, t_env *env);

#endif