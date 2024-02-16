/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_filenames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:51:02 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/16 17:29:58 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_wrong_env_filename(t_redirect *red, char *env_input, int j)
{
	int	x;

	x = 1;
	while (!is_space(red->filename[j]) && val_chars_env(red->filename[j]) == 0
		&& x++)
		j++;
	if ((int)ft_strlen(red->filename) == x)
		red->ambiguos = 1;
	else
		red->filename = change_exit(red->filename, "", (ft_strlen(env_input)
					+ 1));
	free(env_input);
}

int	handle_file(int *j, t_redirect *red, t_env *tmp_l_env)
{
	int		start;
	char	*env_input;

	start = *j;
	while (!is_space(red->filename[*j])
		&& val_chars_env(red->filename[*j]) == 0)
		(*j)++;
	env_input = ft_substr(red->filename, start, (*j - start));
	*j = 0;
	if (search_env(&red->filename, tmp_l_env, env_input) == NULL)
	{
		change_wrong_env_filename(red, env_input, start);
		return (1);
	}
	free(env_input);
	return (0);
}

int	command_expansion_filename(t_redirect *red, t_env *tmp_l_env,
		int exit_status)
{
	int	j;

	j = 0;
	while (red->filename[j] != '\0')
	{
		check_expansion_quotes(red->filename, &j);
		if (red->filename[j] == '$')
		{
			if (find_exception(red->filename, j) == 1)
				break ;
			j++;
			while (red->filename[j] == '$')
				j++;
			if (handle_exit_status(&red->filename, j, exit_status) == 1)
				continue ;
			if (handle_file(&j, red, tmp_l_env) == 1)
				break ;
		}
		if (red->filename[j] != '\0')
			j++;
	}
	return (0);
}
