/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:17 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 10:57:23 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cont_pipe(char const *s)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (s[i] != '\0')
	{
        if(s[i] == '|')
            result++;
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
            {
                i++;			
            }
        }
        if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
            {
                i++;				
            }
        }
		i++;
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

    index = *i; 
	while (s[*i] != '\0')
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
        }
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
	int		i = 0;
	int		j = 0;
	int 	len;
	int count;

	count = cont_pipe(s);

	len = ft_strlen(s);
	totals = malloc(sizeof(char *) * (count + 1));

	if (totals == NULL)
		return (NULL);

	while (i < len)
	{
		totals[j] = cont_word(s, &i);
		j++;
	}
	totals[j] = NULL;
	return (totals);
}
