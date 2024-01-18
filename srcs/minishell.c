/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/18 11:48:17 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


// static int	start_execution(char *input, t_env **my_env)
// {
// 	int	exit_status;

// 	exit_status = one_cmd(input, my_env);
// 	return (exit_status);
// }

int	minishell(t_env *my_env)
{
	char	*input;
	int		exit_status;

	(void)my_env;
	while (1)
	{
		init_signal();
		input = readline(get_prompt());
		if (!input)
			(ft_exit(NULL, &my_env));
		if (input[0])
			add_history(input);
		// função check args
		if (validate_input(input) == 1)
		{
			continue;
		}
		parsing(input); //se tudo tiver ok eu faço o parsing
		//exit_status = start_execution(input, &my_env);
	}
	return (exit_status);
}
