/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/02/10 11:14:39 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	start_execution(t_dados *data, t_env **my_env)
// {
// 	int	exit_status;

// 	if (!data->next)
// 		exit_status = ft_one_cmd(data, my_env);
// 	else
// 		exit_status = ft_execute_multiple_cmd(data, *my_env);
// 	return (exit_status);
// }

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

// antes do exit_status receber qualquer coisa vamos chamar o parsing
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
				parse_heredoc(dados);
				exit_status = start_execution(dados, &my_env);
				//exit_status = exec_testes(dados, &my_env);
				free_list(&dados);
			}
		}
		else
			exit_status = tmp_exit;
		free(input);
	}
	return (exit_status);
}
