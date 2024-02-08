/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:08:31 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 15:27:37 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	val_chars_env(char c)
{
	if (c == 95 || c == 29 || c == 28)
		return (0);
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (0);
	return (1);
}

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (c != s[i])
	{
		if (s[i] == 0)
			return (-1);
		i++;
	}
	return (i);
}

int	find_exception(char *cmd_input, int j)
{
	j++;
	if (cmd_input[j] == '"' || cmd_input[j] == '\'')
		return (1);
	if (cmd_input[j] == '\0' || cmd_input[j] == ' ' || cmd_input[j] == '\t')
		return (1);
	return (0);
}

void	check_expansion_quotes(char *command, int *j)
{
	static int	flag;

	if (command[*j] == '"' && flag == 0)
		flag = 1;
	else if (command[*j] == '"' && flag == 1)
		flag = 0;
	if (command[*j] == '\'' && flag == 0)
	{
		while (command[++(*j)] != '\'')
			;
	}
}

t_env	*search_env(char **command, t_env *tmp_env, char *env_input)
{
	int	index;

	while (tmp_env != NULL)
	{
		index = find_char(tmp_env->key, '=');
		if ((size_t)index == ft_strlen(env_input))
		{
			if (ft_strncmp(tmp_env->key, env_input, ft_strlen(env_input)) == 0)
			{
				*command = change_input(command, tmp_env->key, index);
				break ;
			}
		}
		tmp_env = tmp_env->next;
	}
	return (tmp_env);
}
