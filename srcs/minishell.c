/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2023/12/28 10:10:21 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	start_execution(char *input, t_env **my_env)
{
	int	exit_status;

	exit_status = ft_one_cmd(input, my_env);
	return (exit_status);
}

int	minishell(t_env *my_env)
{
	char	*input;
	int		exit_status;

	(void)my_env;
	while (1)
	{
		ft_init_signal();
		input = readline(ft_get_prompt());
		if (!input)
			(ft_exit(NULL, &my_env));
		if (input[0])
			add_history(input);
		exit_status = start_execution(input, &my_env);
	}
	return (exit_status);
}
