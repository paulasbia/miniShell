/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 14:55:27 by ricardo          ###   ########.fr       */
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

int	quotes_len(char *s)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
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
	return (size);
}

void	handle_quotes(int *i, int *j, char *new_string, char *s)
{
	(*i)++;
	while (s[(*i)] != '\'')
		new_string[(*j)++] = s[(*i)++];
	(*i)++;
}

char	*clean_quotes(char *s)
{
	int		i;
	int		j;
	char	*new_string;

	i = 0;
	j = 0;
	new_string = malloc((sizeof(char) * quotes_len(s)) + 1);
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			handle_quotes(&i, &j, new_string, s);
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
