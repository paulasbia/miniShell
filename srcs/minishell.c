/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/31 18:27:50 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_execution(t_dados *data, t_env **my_env)
{
	int	exit_status;

	if (!data->next)
		exit_status = ft_one_cmd(data, my_env);
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

int	check_heredoc(t_dados *data, t_dados **data_out, int *red_out)
{
	int	i;

	*data_out = NULL;
	i = 0;
	while (data)
	{
		while (i < data->nbr_redirections)
		{
			if (data->redirect->redirect_type == 2)
			{
				*red_out = i;
				*data_out = data;
			}
			i++;
		}
		data = data->next;
		i = 0;
	}
	return (*data_out != NULL);
}

t_dados	*parse_heredoc(t_dados *dados)
{
	char	*input;
	t_dados	*temp;
	int		i;
	int		fd;

	if (check_heredoc(dados, &temp, &i))
	{
		fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		input = readline("> ");
		while (input && !str_equal(input, temp->redirect[i].filename))
		{
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			free(input);
			input = readline("> ");
		}
		free(input);
		close(fd);
		temp->redirect[i].filename = "/tmp/heredoc";
	}
	return (dados);
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
				dados = parse_heredoc(dados);
				exit_status = start_execution(dados, &my_env);
				free_list(&dados);
			}
		}
		free(input);
	}
	return (exit_status);
}
