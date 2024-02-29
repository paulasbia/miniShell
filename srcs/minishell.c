/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/02/29 16:13:25 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(t_env **my_env)
{
	char	*input;

	input = readline(ft_get_prompt());
	if (!input)
		(ft_exit(NULL, my_env));
	if (input[0])
		add_history(input);
	return (input);
}

int	ft_start(int *exit_status, t_dados *dados, t_env **my_env)
{
	if (*exit_status != 130)
		*exit_status = start_execution(dados, my_env);
	else
		start_execution(dados, my_env);
	return (*exit_status);
}

int	minishell(t_env *my_env, int exit_status)
{
	t_dados	*dados;
	int		tmp_exit;
	char	*input;

	while (1)
	{
		ft_init_signal();
		input = get_input(&my_env);
		tmp_exit = validate_input(input);
		if (tmp_exit == 0)
		{
			dados = parsing(input, my_env, exit_status);
			if (dados)
			{
				exit_status = parse_heredoc(dados);
				exit_status = ft_start(&exit_status, dados, &my_env);
				free_list(&dados);
			}
		}
		else
			exit_status = tmp_exit;
		free(input);
	}
	return (exit_status);
}
