/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 12:13:42 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_dp(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_list(t_dados **lst)
{
	t_dados	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free_dp(temp->comando);
		while (temp->nbr_redirections > 0)
		{
			free(temp->redirect[temp->nbr_redirections - 1].filename);
			temp->nbr_redirections--;
		}
		free(temp->redirect);
		free(temp);
		temp = NULL;
	}
	free(*lst);
	*lst = NULL;
}

char	*alloc_clean_quotes(int size, char *s, int j, int i)
{
	char	*new_string;

	new_string = malloc((sizeof(char) * size) + 1);
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				new_string[j++] = s[i++];
			i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				new_string[j++] = s[i++];
			i++;
		}
		else
			new_string[j++] = s[i++];
	}
	new_string[j] = '\0';
	return (new_string);
}

char	*clean_quotes(char *s)
{
	int		i;
	int		size;
	char	*new_string;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i++] == '\'')
		{
			i++;
			while (s[i++] != '\'')
				size++;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i++] != '"')
				size++;
		}
		i++;
		size++;
	}
	new_string = alloc_clean_quotes(size, s, 0, 0);
	return (new_string);
}
