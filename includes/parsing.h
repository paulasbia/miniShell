/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:07 by paula             #+#    #+#             */
/*   Updated: 2024/01/15 14:02:33 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

typedef struct s_redireção
{
	int				tipo_de_redireção;
	char			*filenane;
}					t_redireção;

typedef struct s_dados
{
	char			**comando;
	t_redireção		*redireção;
	struct s_dados	*next;
}					t_dados;

void				parsing(char *input);

#endif