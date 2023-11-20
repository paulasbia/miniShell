/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:23:54 by pde-souz          #+#    #+#             */
/*   Updated: 2023/08/24 11:48:09 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
	{
		return (0);
	}
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*nstr;
	char	*ret;
	int		i;

	if (s2[0] == '\0')
		return (0);
	i = 0;
	nstr = (char *)malloc(sizeof(char) * ft_strlen_gnl(s1) + BUFFER_SIZE + 1);
	ret = nstr;
	if (nstr == 0)
	{
		free(nstr);
		return (NULL);
	}
	while (s1 != 0 && s1[i] != 0)
		*nstr++ = s1[i++];
	if (s1 != 0)
		free(s1);
	while (s2 != 0 && *s2 != 0 && *s2 != '\n')
		*nstr++ = *s2++;
	if (*s2 == '\n')
		*nstr++ = '\n';
	*nstr = 0;
	return (ret);
}

int	ft_find_nl(char *str)
{
	int	i;
	int	j;
	int	new_line;

	i = 0;
	j = 0;
	new_line = 0;
	while (str[i] != 0 && str[i] != '\n')
		str[i++] = '\0';
	if (str[i] == '\n')
	{
		new_line = 1;
		str[i++] = '\0';
		while (str[i] != 0)
		{
			str[j++] = str[i];
			str[i++] = '\0';
		}
	}
	return (new_line);
}
