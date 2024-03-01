/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:32:18 by paula             #+#    #+#             */
/*   Updated: 2024/03/01 11:16:27 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	getcwd(cwd, PATH_MAX);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
