/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:23 by paula             #+#    #+#             */
/*   Updated: 2024/02/02 09:43:43 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_path(char *cmd, t_env *my_env)
{
	char	*path_env;
	char	*cmd_path;
	char	*temp;
	char	**paths;
	int		i;

	path_env = mini_value("PATH", my_env);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(cmd_path, F_OK))
		{
			ft_clean(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_clean(paths);
	return (0);
}

void	external_exit(char **args, t_env *minienv, int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		print_error_msg(args[0], NOT_EXECUTABLE_MSG);
	if (exit_status == CMD_NOT_FOUND)
		print_error_msg(args[0], CMD_NOT_FOUND_MSG);
	rl_clear_history();
	ft_free_env(&minienv);
	ft_free_args(args);
	exit(exit_status);
}

static int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*command == '.')
			command++;
		if (*command == '.')
			command++;
		if (*command == '/')
			return (1);
	}
	return (0);
}

void	ft_check_exit(char **args, t_env *my_env)
{
	if (!args[0])
		external_exit(args, my_env, EXIT_SUCCESS);
	if (is_folder(args[0]))
		external_exit(args, my_env, NOT_EXECUTABLE);
}

int	ft_exec_child_process(char **args, t_env *my_env)
{
	char	*path;
	char	**env_array;
	char	*value;

	ft_check_exit(args, my_env);
	value = mini_value("PATH", my_env);
	if (ft_strchr(args[0], '/') || !value)
		path = ft_strdup(args[0]);
	else
		path = ft_get_path(args[0], my_env);
	if (path == NULL)
		external_exit(args, my_env, CMD_NOT_FOUND);
	rl_clear_history();
	env_array = myenv_to_array(my_env);
	ft_free_env(&my_env);
	if (execve(path, args, env_array))
		ft_handle_errors(args, path, env_array);
	exit(EXIT_SUCCESS);
}
