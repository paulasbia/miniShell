/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:56:43 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 10:56:49 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cont(char const *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if(s[i] == '\0')
		{
			return result;

		}
		while (s[i] != '\0'  && s[i] != ' ' && s[i] != '\t')
		{
			if(s[i] == '"')
			{
				i++;
				while(s[i] != '"')
				{
					i++;			
				}
				if(s[i] == ' ' || s[i] == '\t')
				{
					result++;
				}
				if (s[i] == '\0')
					return result + 1;
			}
			if(s[i] == '\'')
			{
				i++;
				while(s[i] != '\'')
				{
					i++;				
				}
				if(s[i] == ' ' || s[i] == '\t')
				{
					result++;
				}
				if (s[i] == '\0')
					return result + 1;
			}
			if(s[i] == '<' || s[i] == '>')
			{
				if(i > 0 && s[i - 1] != ' ' && s[i] != '\t')
				{
					result++;
				}
				while(s[i + 1] == '>' || s[i + 1] == '<')
				{
					i++;
				}
				if(s[i + 1] != ' ' && s[i + 1] != '\t' && s[i + 1] != '\0')
				{
					result++;
				}
			}
			if (s[i])
				i++;
		}
		result++;
	}
	return (result);
}


static char *alloc_word(const char *s, int j, int index)
{
	char *src;
	int i = 0;

	src = malloc(sizeof(char) * (j + 1));
	if (src == NULL)
		return (NULL);
	while(j > 0)
	{
		src[i++] = s[index++];
		j--;
	}
	src[i] = '\0';	
	return (src);
}

static char	*cont_word(char const *s, int *i)
{
    int j = 0;
	int index;
	static int help = 0;

	while (s[*i] != '\0')
	{
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		
		index = *i; 
		while (s[*i] != '\0'  && s[*i] != ' ' && s[*i] != '\t')
		{
			if(s[*i] == '"')
			{
				(*i)++;
				j++;
				while(s[*i] != '"')
				{
					(*i)++;
					j++;		
				}
				if(s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
				{
					return (alloc_word(s, j, index));
				}
			}
			if(s[*i] == '\'')
			{
				(*i)++;
				j++;
				while(s[*i] != '\'')
				{
					(*i)++;
					j++;			
				}
				if(s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0')
				{
					return (alloc_word(s, j, index));
				}
			}
			if(s[*i] == '<' || s[*i] == '>')
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
				while(s[*i] == '>' || s[*i] == '<')
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
	int		i = 0;
	int		j = 0;
	int count;

	count = cont(s);
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