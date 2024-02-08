/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_changes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:09:50 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 23:11:21 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

void	move_empty_command(char **cmd, int i)
{
	int	help;

	help = 0;
	while (cmd[i] != NULL || help == 0)
	{
		cmd[i] = cmd[i + 1];
		help = 1;
		i++;
	}
	cmd[i] = NULL;
}

char	*change_input(char **cmd_input, char *key, int size_index_env)
{
	char			*result;
	t_int_parsing	ie;

	ie.i = 0;
	ie.j = 0;
	ie.x = size_index_env + 1;
	result = malloc(sizeof(char) * (ft_strlen(*cmd_input) + ((int)ft_strlen(key)
					- ie.x) - ie.x + 1));
	while ((*cmd_input)[ie.i] != '\0' && (*cmd_input)[ie.i] != '$')
		result[ie.j++] = (*cmd_input)[ie.i++];
	while (key[ie.x] != '\0')
		result[ie.j++] = key[ie.x++];
	ie.i = ie.i + size_index_env + 1;
	while ((*cmd_input)[ie.i] != '\0')
		result[ie.j++] = (*cmd_input)[ie.i++];
	result[ie.j] = '\0';
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
	while (!is_space(command[i][j]) && val_chars_env(command[i][j]) == 0 && x++)
		j++;
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
