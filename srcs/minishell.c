/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/30 20:07:37 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_execution(t_dados *data, t_env **my_env)
{
	int	exit_status;

	if (!data->next && str_equal(data->comando[0], "exit"))
		exit_status = ft_exit(data, my_env);
	else
		exit_status = ft_execute_multiple_cmd(data, *my_env);
	return (exit_status);
}

// um fake apenas para poder executar testes com a entrada t_dados
t_dados	*fake_parser(char *input)
{
	t_dados	*parsed;

	parsed = malloc(sizeof(t_dados));
	parsed->comando = ft_split(input, ' ');
	parsed->nbr_redirections = 0;
	parsed->redirect = NULL;
	parsed->next = NULL;
	return (parsed);
}

// antes do exit_status receber qualquer coisa vamos chamar o parsing
int	minishell(t_env *my_env)
{
	char	*input;
	int		exit_status;
	t_dados	*dados;

	while (1)
	{
		ft_init_signal();
		input = readline(ft_get_prompt());
		if (!input)
			(ft_exit(NULL, &my_env));
		if (input[0])
			add_history(input);
		if (validate_input(input) == 0)
		{
			dados = parsing(input);
			if (dados)
			{
				exit_status = start_execution(dados, &my_env);
				free_list(&dados);				
			}
		}
		free(input);
	}
	return (exit_status);
}
