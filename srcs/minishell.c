/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/24 11:03:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

int	start_execution(t_dados *data, t_env **my_env)
{
	int	exit_status;

	if (!data->next)
		exit_status = ft_one_cmd(data, my_env);
	ft_free_data(data);
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
	t_dados *dados;

	(void)my_env;
	while (1)
	{
		ft_init_signal();
		input = readline(ft_get_prompt());
		if (!input)
			(ft_exit(NULL, &my_env));
		if (input[0])
			add_history(input);
		// função check args
		if (validate_input(input) == 0)
		{
			dados = parsing(input); //se tudo tiver ok eu faço o parsing;
			free_list(&dados);
		}
		exit_status = start_execution(fake_parser(input), &my_env);
		free(input);
	}
	return (exit_status);
}
