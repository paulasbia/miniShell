/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:56:43 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/02 22:27:34 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_word_quotes(int *i, int *j, char const *s, char c)
{
	(*i)++;
	(*j)++;
	while (s[*i] != c)
	{
		(*i)++;
		(*j)++;
	}
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

static char	*cont_word(char const *s, int *i)
{
	int			j;
	int			index;
	static int	help;

	j = 0;
	help = 0;
	while (s[*i] != '\0')
	{
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		index = *i;
		while (s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t')
		{
			if (s[*i] == '"')
			{
				handle_word_quotes(i, &j, s, '"');
				if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
					return (alloc_word(s, j, index));
			}
			if (s[*i] == '\'')
			{
				handle_word_quotes(i, &j, s, '\'');
				if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
					return (alloc_word(s, j, index));
			}
			if (s[*i] == '<' || s[*i] == '>')
			{
				if (*i > 0 && s[(*i - 1)] != ' ' && help == 0)
				{
					help = 1;
					return (alloc_word(s, j, index));
				}
				else
					help = 0;
				j++;
				(*i)++;
				while (s[*i] == '>' || s[*i] == '<')
				{
					(*i)++;
					j++;
				}
				return (alloc_word(s, j, index));
			}
			(*i)++;
			j++;
		}
		return (alloc_word(s, j, index));
	}
	return (NULL);
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
		totals[j] = cont_word(s, &i);
		j++;
	}
	totals[j] = NULL;
	return (totals);
}
