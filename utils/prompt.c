/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:04:13 by paula             #+#    #+#             */
/*   Updated: 2023/12/15 15:16:07 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(void)
{
	char		*name;
	static char	prompt[PATH_MAX];

	name = PROMPT;
	ft_bzero(prompt, sizeof(prompt));
	ft_strlcat(prompt, GRN, PATH_MAX);
	ft_strlcat(prompt, name, PATH_MAX);
	ft_strlcat(prompt, CRESET, PATH_MAX);
	return (prompt);
}
