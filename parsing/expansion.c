/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:35:21 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/16 12:49:19 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	handle_command(int *j, char **cmd, t_env *tmp_l_env, t_dados *n)
{
	int		start;
	char	*env_input;

	start = *j;
	while (!is_space((*cmd)[*j]) && val_chars_env((*cmd)[*j]) == 0)
		(*j)++;
	env_input = ft_substr((*cmd), start, (*j - start));
	*j = 0;
	if (search_env(cmd, tmp_l_env, env_input) == NULL)
	{
		change_wrong_env(n->cmd, env_input, *cmd, start);
		return (1);
	}
	free(env_input);
	return (0);
}

int	command_expansion(t_dados *n, char **cmd, t_env *tmp_l_env, int exit_status)
{
	int	j;

	j = 0;
	while ((*cmd)[j] != '\0')
	{
		check_expansion_quotes((*cmd), &j);
		if ((*cmd)[j] == '$')
		{
			if (find_exception((*cmd), j) == 1)
				break ;
			j++;
			while ((*cmd)[j] == '$')
				j++;
			if (handle_exit_status(cmd, j, exit_status) == 1)
				continue ;
			if (handle_command(&j, cmd, tmp_l_env, n) == 1)
				break ;
		}
		if ((*cmd)[j] != '\0')
			j++;
	}
	return (0);
}

int	expansion(t_dados *n, t_env *env, int exit_status)
{
	int		i;
	t_env	*tmp_l_env;

	i = 0;
	while (n->cmd[i] != NULL)
	{
		tmp_l_env = env;
		command_expansion(n, &n->cmd[i], tmp_l_env, exit_status);
		i++;
	}
	i = 0;
	while (i < n->nbr_redirections)
	{
		tmp_l_env = env;
		if(n->redirect[i].redirect_type != 2)
			command_expansion_filename(&n->redirect[i], tmp_l_env, exit_status);
		i++;
	}
	return (0);
}
