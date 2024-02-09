/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:57:01 by paula             #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_cd(char *path, t_env **my_env)
{
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (chdir(path) != 0)
	{
		ft_cd_err_msg(path);
		return (EXIT_FAILURE);
	}
	pwd = mini_value("PWD", *my_env);
	oldpwd = mini_value("OLDPWD", *my_env);
	if (!oldpwd)
	{
		ft_add_list("OLDPWD=", my_env);
		ft_update_envlist("OLDPWD", pwd, *my_env);
	}
	if (oldpwd && pwd && *pwd)
		ft_update_envlist("OLDPWD", pwd, *my_env);
	if (pwd && *pwd)
		ft_update_envlist("PWD", getcwd(cwd, PATH_MAX), *my_env);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_dados *data, t_env **my_env)
{
	char	*path;

	if (data->cmd[1] && data->cmd[2])
	{
		print_error_msg("cd", "too many arguments");
		return (EXIT_FAILURE);
	}
	if (!data->cmd[1] || !ft_strncmp(data->cmd[1], "~", 1))
		path = mini_value("HOME", *my_env);
	else
		path = data->cmd[1];
	if (ft_execute_cd(path, my_env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
