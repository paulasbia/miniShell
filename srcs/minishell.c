/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:09:35 by paula             #+#    #+#             */
/*   Updated: 2024/01/12 17:04:18 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*ft_check_fds(char *input, int *fds)
{
	int	open_flags;

	while (*input)
	{
		if (*input == '>')
		{
			input++;
			if (*input == '>')
			{
				open_flags = O_WRONLY | O_CREAT | O_APPEND;
				fds[STDOUT_FILENO] = open("teste", open_flags, 0644);
				return(fds);
			}
			else
			{
				open_flags = O_WRONLY | O_CREAT | O_TRUNC;
				fds[STDOUT_FILENO] = open("teste", open_flags, 0644);
				return(fds);		
			}
		}
		input++;
	}
	fds[STDOUT_FILENO] = STDOUT_FILENO;
	return(fds);
}

static int	start_execution(char *input, t_env **my_env)
{
	int	exit_status;
	int	fd[2];

	ft_check_fds(input, fd);
	//ler o imput, IF tiver '>' entao open, se for >> APPEND
	//fd[STDOUT_FILENO] = open("teste", O_WRONLY);

	exit_status = ft_one_cmd(input, my_env, fd);
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
