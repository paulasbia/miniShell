/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:22:49 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/12 11:02:40 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_count_ms(int *i, const char *s, int *result, char c)
{
	(*i)++;
	while (s[*i] != c)
		(*i)++;
	if (s[*i] == ' ' || s[*i] == '\t')
		(*result)++;
}

void	handle_count_redirection(int *i, const char *s, int *result)
{
	if ((*i) > 0 && s[(*i) - 1] != ' ' && s[*i] != '\t')
		(*result)++;
	while (s[(*i) + 1] == '>' || s[(*i) + 1] == '<')
		(*i)++;
	if (s[(*i) + 1] != ' ' && s[(*i) + 1] != '\t' && s[(*i) + 1] != '\0')
		(*result)++;
}

int	handle_count_loop(char const *s, int result, int *i)
{
	while (s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t')
	{
		if (s[*i] == '"')
		{
			handle_count_ms(i, s, &result, '"');
			if (s[*i] == '\0')
				return (result + 1);
		}
		if (s[*i] == '\'')
		{
			handle_count_ms(i, s, &result, '\'');
			if (s[*i] == '\0')
				return (result + 1);
		}
		if (s[*i] == '<' || s[*i] == '>')
			handle_count_redirection(i, s, &result);
		if (s[*i])
			(*i)++;
	}
	return (result + 1);
}

int	count_split_ms(char const *s)
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
		result = handle_count_loop(s, result, &i);
		if (s[i] == '\0')
			return (result);
	}
	return (result);
}
