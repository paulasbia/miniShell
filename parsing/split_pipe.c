/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:17 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/05 20:26:40 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cont_pipe(char const *s)
{
	int	result;

	result = 1;
	while (*s != '\0')
	{
		if (*s == '|')
			result++;
		if (*s == '"')
		{
			s++;
			while (*s != '"')
				s++;
		}
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
				s++;
		}
		s++;
	}
	return (result);
}

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

void	handle_quotes_on_pipe(int *i, int *j, char const *s, char c)
{
	(*i)++;
	(*j)++;
	while (s[*i] != c)
	{
		(*i)++;
		(*j)++;
	}
}

static char	*cont_word_pipe(char const *s, int *i)
{
	int	j;
	int	index;

	j = 0;
	index = *i;
	while (s[*i] != '\0')
	{
		if (s[*i] == '"')
			handle_quotes_on_pipe(i, &j, s, '"');
		if (s[*i] == '\'')
			handle_quotes_on_pipe(i, &j, s, '\'');
		if (s[*i] == '|')
		{
			(*i)++;
			return (alloc_word(s, j, index));
		}
		j++;
		(*i)++;
	}
	return (alloc_word(s, j, index));
}

char	**split_pipe(char const *s)
{
	char	**totals;
	int		i;
	int		j;
	int		len;
	int		count;

	i = 0;
	j = 0;
	count = cont_pipe(s);
	len = ft_strlen(s);
	totals = malloc(sizeof(char *) * (count + 1));
	if (totals == NULL)
		return (NULL);
	while (i < len)
	{
		totals[j] = cont_word_pipe(s, &i);
		j++;
	}
	totals[j] = NULL;
	return (totals);
}
