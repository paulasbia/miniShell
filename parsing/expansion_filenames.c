/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_filenames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:51:02 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 23:16:58 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	handle_file(int *j, char **file, t_env *tmp_l_env, t_dados *n)
// {
// 	int		start;
// 	char	*env_input;

// 	start = *j;
// 	while (!is_space((*file)[*j]) && val_chars_env((*file)[j]) == 0)
// 		(*j)++;
// 	env_input = ft_substr((*file), start, (*j - start));
// 	*j = 0;
// 	if (search_env(file, tmp_l_env, env_input) == NULL)
// 	{
// 		change_wrong_env_filename(n->redirect, env_input, file, start);
// 		return (1);
// 	}
// 	free(env_input);
// 	return (0);
// }

// int	command_expansion_filename(t_dados *n, char **file, t_env *tmp_l_env,
//		int exit_status)
// {
// 	int	j;

// 	j = 0;
// 	while ((*file)[j] != '\0')
// 	{
// 		check_expansion_quotes(*file, &j);
// 		if ((*file)[j] == '$')
// 		{
// 			if (find_exception(*file, j) == 1)
// 				break ;
// 			j++;
// 			while ((*file)[j] == '$')
// 				j++;
// 			if (handle_exit_status(file, j, exit_status) == 1)
// 				continue ;
// 			if (handle_file(&j, file, tmp_l_env, n) == 1)
// 				break ;
// 		}
// 		if ((*file)[j] != '\0')
// 			j++;
// 	}
// 	return (0);
// }

// void	change_wrong_env_filename(char *filename, char *env_input,
//		char *replace, int j)
// {
// 	int	x;
// 	int	i;

// 	i = 0;
// 	while (filename[i] != NULL)
// 	{
// 		if (filename[i] == replace)
// 			break ;
// 		i++;
// 	}
// 	x = 1;
// 	if (filename[0] == '"')
// 		x += 2;
// 	while (!is_space(filename[j]) && val_chars_env(filename[j]) == 0 && x++)
// 		j++;
// 	if ((int)ft_strlen(filename) == x)
// 	{
// 		free(filename);
// 		filename = NULL;
// 		move_empty_command(filename, i--);
// 	}
// 	else
// 		filename = change_exit(filename, "", (ft_strlen(env_input) + 1));
// 	free(env_input);
// }
