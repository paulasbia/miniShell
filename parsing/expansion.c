/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:35:21 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/07 23:53:15 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_input(char **cmd_input, char *key, int size_index_env)
{
	char	*result;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = size_index_env + 1;
	result = malloc(sizeof(char) * (ft_strlen(*cmd_input) + ((int)ft_strlen(key)
					- x) - x + 1));
	while ((*cmd_input)[i] != '\0' && (*cmd_input)[i] != '$')
		result[j++] = (*cmd_input)[i++];
	while (key[x] != '\0')
		result[j++] = key[x++];
	i = i + size_index_env + 1;
	while ((*cmd_input)[i] != '\0')
		result[j++] = (*cmd_input)[i++];
	result[j] = '\0';
	free((*cmd_input));
	return (result);
}

char	*change_exit(char *cmd_input, char *string_exit, int size)
{
	char	*result;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	result = malloc(sizeof(char) * (ft_strlen(cmd_input) - size
				+ ft_strlen(string_exit) + 1));
	while (cmd_input[i] != '\0' && cmd_input[i] != '$')
		result[j++] = cmd_input[i++];
	while (string_exit[x] != '\0')
		result[j++] = string_exit[x++];
	i += size;
	while (cmd_input[i] != '\0')
		result[j++] = cmd_input[i++];
	result[j] = '\0';
	free(cmd_input);
	return (result);
}

void	change_wrong_env(char **command, char *env_input, char *replace, int j)
{
	int	x;
	int	i;

	i = 0;
	while (command[i] != NULL)
	{
		if (command[i] == replace)
			break ;
		i++;
	}
	x = 1;
	if (command[i][0] == '"')
		x += 2;
	while (command[i][j] != '\0' && command[i][j] != ' '
		&& command[i][j] != '\t' && validate_chars_env(command[i][j]) == 0)
	{
		x++;
		j++;
	}
	if ((int)ft_strlen(command[i]) == x)
	{
		free(command[i]);
		command[i] = NULL;
		move_empty_command(command, i--);
	}
	else
		command[i] = change_exit(command[i], "", (ft_strlen(env_input) + 1));
	free(env_input);
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

int	handle_exit_status(char **command, int j, int exit_status)
{
	char	*string_exit;

	if ((*command)[j] == '?')
	{
		string_exit = ft_itoa(exit_status);
		*command = change_exit(*command, string_exit, 2);
		free(string_exit);
		return (1);
	}
	return (0);
}

int	command_expansion(t_dados *n, char **command, t_env *tmp_l_env,
		int exit_status)
{
	int		j;
	char	*env_input;
	int		start;

	j = 0;
	start = 0;
	while ((*command)[j] != '\0')
	{
		check_expansion_quotes((*command), &j);
		if ((*command)[j] == '$')
		{
			if (find_exception((*command), j) == 1)
				break ;
			j++;
			while ((*command)[j] == '$')
				j++;
			if (handle_exit_status(command, j, exit_status) == 1)
				continue ;
			start = j;
			while ((*command)[j] != '\0' && (*command)[j] != ' '
					&& (*command)[j] != '\t'
					&& validate_chars_env((*command)[j]) == 0)
				j++;
			env_input = ft_substr((*command), start, (j - start));
			if (search_env(command, tmp_l_env, env_input) == NULL)
			{
				change_wrong_env(n->comando, env_input, *command, start);
				break ;
			}
			free(env_input);
		}
		if ((*command)[j] != '\0')
			j++;
	}
	return (0);
}

int	expansion(t_dados *n, t_env *env, int exit_status)
{
	int		i;
	t_env	*tmp_l_env;

	i = 0;
	while (n->comando[i] != NULL)
	{
		tmp_l_env = env;
		command_expansion(n, &n->comando[i], tmp_l_env, exit_status);
		i++;
	}
	return (0);
}
