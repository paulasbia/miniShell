/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:26:21 by paula             #+#    #+#             */
/*   Updated: 2023/12/27 17:30:40 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*varname(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '=' && name[i])
		i++;
	return (ft_substr(name, 0, i));
}

char	*varvalue(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i])
		i++;
	if (!value[i])
		return (NULL);
	return (&value[i + 1]);
}
