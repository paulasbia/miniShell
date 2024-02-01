/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:42:53 by paula             #+#    #+#             */
/*   Updated: 2024/02/01 09:43:13 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
