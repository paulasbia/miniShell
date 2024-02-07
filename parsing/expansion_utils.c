/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:08:31 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/07 23:40:07 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_chars_env(char c)
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

void	move_empty_command(char **comando, int i)
{
	int	help;

	help = 0;
	while (comando[i] != NULL || help == 0)
	{
		comando[i] = comando[i + 1];
		help = 1;
		i++;
	}
	comando[i] = NULL;
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
