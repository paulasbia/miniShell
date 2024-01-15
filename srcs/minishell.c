/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/15 16:53:01 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	start_execution(t_dados *parsed, t_env **my_env)
{
	int	exit_status;
	char	*input;

	input = parsed->comando[0];
	exit_status = ft_one_cmd(input, my_env);
	return (exit_status);
}

int	minishell(t_env *my_env)
{
	char	*input;
	int		exit_status;
	t_dados	*parsed;

	(void)my_env;
	while (1)
	{
		ft_init_signal();
		input = readline(ft_get_prompt());
		if (!input)
			(ft_exit(NULL, &my_env));
		if (input[0])
			add_history(input);
		parsed = parsing(input);
		exit_status = start_execution(parsed, &my_env);
	}
	return (exit_status);
}
