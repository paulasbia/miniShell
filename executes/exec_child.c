/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:53:23 by paula             #+#    #+#             */
/*   Updated: 2024/01/04 10:50:58 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	minienv_size(t_env *my_env)
{
	int	i;

	if (!my_env)
	{
		return (0);
	}
	i = 0;
	while (my_env != 0)
	{
		i++;
		my_env = my_env->next;
	}
	return (i);
}

char	**myenv_to_array(t_env *my_env)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(my_env) + 1));
	aux = my_env;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->key);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}

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
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(paths);
	return (0);
}

int	ft_exec_child_process(char **args, t_env *my_env)
{
	char	*path;
	char	**env_array;

	path = ft_get_path(args[0], my_env);
	env_array = myenv_to_array(my_env);
	execve(path, args, env_array);
	return (EXIT_SUCCESS);
}
