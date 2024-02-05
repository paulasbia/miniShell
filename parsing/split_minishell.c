/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:56:43 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/05 20:24:25 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc_word(const char *s, int j, int index)
{
	char	*src;
	int		i;

	i = 0;
	src = malloc(sizeof(char) * (j + 1));
	if (src == NULL)
		return (NULL);
	while (j > 0)
	{
		src[i++] = s[index++];
		j--;
	}
	src[i] = '\0';
	return (src);
}

char	*tata_2(char const *s, int *i, int *j, int *index)
{
	static int	help;

	if (s[*i] == '<' || s[*i] == '>')
	{
		if (*i > 0 && s[(*i - 1)] != ' ' && help == 0)
		{
			help = 1;
			return (alloc_word(s, *j, *index));
		}
		else
			help = 0;
		(*j)++;
		(*i)++;
		while (s[*i] == '>' || s[*i] == '<')
		{
			(*i)++;
			(*j)++;
		}
		return (alloc_word(s, *j, *index));
	}
	return (NULL);
}

char	*handle_both_quotes(char const *s, int *i, int *index, int *j)
{
	if (s[*i] == '"')
	{
		(*i)++;
		(*j)++;
		while (s[*i] != '"')
		{
			(*i)++;
			(*j)++;
		}
		if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
			return (alloc_word(s, *j, *index));
	}
	if (s[*i] == '\'')
	{
		(*i)++;
		(*j)++;
		while (s[*i] != '\'')
		{
			(*i)++;
			(*j)++;
		}
		if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
			return (alloc_word(s, *j, *index));
	}
	return (NULL);
}

static char	*count_word(char const *s, int *i)
{
	int		j;
	int		index;
	char	*result;

	j = 0;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '\0')
		return (NULL);
	index = *i;
	while (s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t')
	{
		result = handle_both_quotes(s, i, &index, &j);
		if (result != NULL)
			return (result);
		result = tata_2(s, i, &j, &index);
		if (result != NULL)
			return (result);
		(*i)++;
		j++;
	}
	return (alloc_word(s, j, index));
}

char	**split_ms(char const *s)
{
	char	**totals;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = count_split_ms(s);
	totals = malloc(sizeof(char *) * (count + 1));
	if (totals == NULL)
		return (NULL);
	while (j < count)
	{
		totals[j] = count_word(s, &i);
		j++;
	}
	totals[j] = NULL;
	return (totals);
}
