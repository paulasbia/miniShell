/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_split_ms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:49 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 17:02:00 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cont_ms(int *i, const char *s, int *result, char c)
{
	i++;
	while (s[*i] != c)
		(*i)++;
	if (s[*i] == ' ' || s[*i] == '\t')
		(*result)++;
}

void	handle_cont_redirection(int *i, const char *s, int *result)
{
	if ((*i) > 0 && s[(*i) - 1] != ' ' && s[*i] != '\t')
		(*result)++;
	while (s[(*i) + 1] == '>' || s[(*i) + 1] == '<')
		(*i)++;
	if (s[(*i) + 1] != ' ' && s[(*i) + 1] != '\t' && s[(*i) + 1] != '\0')
		(*result)++;
}

int	cont(char const *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '\0')
			return (result);
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		{
			if (s[i] == '"')
			{
				handle_cont_ms(&i, s, &result, '"');
				if (s[i] == '\0')
					return (result + 1);
			}
			if (s[i] == '\'')
			{
				handle_cont_ms(&i, s, &result, '\'');
				if (s[i] == '\0')
					return (result + 1);
			}
			if (s[i] == '<' || s[i] == '>')
				handle_cont_redirection(&i, s, &result);
			if (s[i])
				i++;
		}
		result++;
	}
	return (result);
}
