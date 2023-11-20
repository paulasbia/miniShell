/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulabiazotto <paulabiazotto@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:52:45 by pde-souz          #+#    #+#             */
/*   Updated: 2023/08/18 10:52:11 by paulabiazot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	buffer[BUFFER_SIZE];
	int			c;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > FOPEN_MAX)
		return (NULL);
	str = ft_strjoin_gnl(0, buffer);
	if (ft_find_nl(buffer) > 0)
		return (str);
	c = read(fd, buffer, BUFFER_SIZE);
	if (c < 0)
	{
		free(str);
		return (NULL);
	}
	while (c > 0 || *buffer != 0)
	{
		str = ft_strjoin_gnl(str, buffer);
		if (ft_find_nl(buffer) > 0)
			break ;
		c = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}
