/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:52:42 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/03 14:21:44 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	invalid_token(char token, char *s, int *i)
{
	if (s[*i] == token)
	{
		(*i)++;
		if (s[*i] == token)
			(*i)++;
		while (s[*i] != '\0' && (s[*i] == ' ' || s[*i] == '\t'))
			(*i)++;
		if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] == '\0')
		{
			ft_putstr_fd("syntax error, command not found after token\n", 2);
			return (1);
		}
	}
	return (0);
}

int	invalid_quotes(char token, char *s, int *i)
{
	if (s[*i] == token)
	{
		(*i)++;
		while (s[*i] != token)
		{
			if (s[*i] == '\0')
			{
				ft_putstr_fd("syntax error, open quotes\n", 2);
				return (1);
			}
			(*i)++;
		}
	}
	return (0);
}

int	invalid_pipe(char *s, int *i)
{
	int x;
	
	x  = *i;
	if (s[*i] == '|')
	{
		while(x > 0)
		{
			if(s[x - 1] != ' '|| s[x - 1] == '\t')
				break;
			x--;
		}
		if(x <= 0)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		(*i)++;
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		if (s[*i] == '\0')
		{
			ft_putstr_fd("syntax error, command not found after pipe\n", 2);
			return (1);
		}
		if (s[*i] == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		(*i)--;
	}
	return (0);
}

int	validate_input(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (invalid_token('>', s, &i) || invalid_token('<', s, &i))
			return (1);
		if (invalid_pipe(s, &i))
			return (1);
		if (invalid_quotes('"', s, &i) || invalid_quotes('\'', s, &i))
			return (1);
		i++;
	}
	return (0);
}
