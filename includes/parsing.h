/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:07 by paula             #+#    #+#             */
/*   Updated: 2024/01/15 17:27:45 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_type;

typedef struct s_red
{
	t_type			type;
	char			*filenane;
}					t_red;

typedef struct s_dados
{
	char			**comando;
	t_red			*red;
	struct s_dados	*next;
}					t_dados;

t_dados				*parsing(char *input);

#endif