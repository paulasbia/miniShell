/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2023/12/13 16:08:57 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell(t_env *my_env)
{
	char	*input;

	(void)my_env;
	while (1)
	{
		init_signal();
		input = readline(PROMPT);
		if (!input)
			ft_putstr_fd("exit\n", 1);
		if (ft_strncmp(input, "pwd", 4) == 0)
			pwd();
	}
	return (0);
}
