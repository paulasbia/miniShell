/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/16 18:03:59 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			while (s[i] != '\0' && s[i++] != '\'')
				size++;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i++] != '"')
				size++;
		}
		if (!s[i])
			return (size);
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

char	**clear_dp_quotes(char **split_cmd)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (split_cmd[i] != NULL)
	{
		new = clean_quotes(split_cmd[i]);
		free(split_cmd[i]);
		split_cmd[i] = new;
		i++;
	}
	return (split_cmd);
}

void	handle_clean_quotes(t_dados *node, char **split_cmd)
{
	char	*new;
	int		i;

	node->cmd = clear_dp_quotes(node->cmd);
	i = 0;
	while (i < node->nbr_redirections)
	{
		new = clean_quotes(node->redirect[i].filename);
		free(node->redirect[i].filename);
		node->redirect[i].filename = new;
		i++;
	}
	free_dp(split_cmd);
}
