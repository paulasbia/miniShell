/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:52:42 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/16 17:54:55 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_v(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	invalid_token(char token, char *s, int *i)
{
	(*i)++;
	if (s[*i] == token)
		(*i)++;
	while (s[*i] != '\0' && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] == '\0')
	{
		if (s[*i] == '>')
		{
			if (s[*i + 1] == '>')
				return (error_v("syntax error near unexpected token `>>'"));
			return (error_v("syntax error near unexpected token `>'"));
		}
		else if (s[*i] == '<')
		{
			if (s[*i + 1] == '<')
				return (error_v("syntax error near unexpected token `<<'"));
			return (error_v("syntax error near unexpected token `<'"));
		}
		else if (s[*i] == '|')
			return (error_v("syntax error near unexpected token `|'"));
		return (error_v("syntax error near unexpected token `newline'"));
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
				error_v("syntax error, open quotes");
				return (1);
			}
			(*i)++;
		}
	}
	return (0);
}

int	invalid_pipe(char *s, int *i, int x)
{
	if (s[*i] == '|')
	{
		while (x > 0)
		{
			if (s[x - 1] != ' ' || s[x - 1] == '\t')
				break ;
			x--;
		}
		if (x <= 0)
			return (error_v("syntax error near unexpected token `|'"));
		(*i)++;
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		if (s[*i] == '\0')
			return (error_v("syntax error, command not found after pipe"));
		if (s[*i] == '|')
			return (error_v("syntax error near unexpected token `|'"));
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
		if (s[i] == '>')
		{
			if (invalid_token('>', s, &i))
				return (2);
		}
		if (s[i] == '<')
		{
			if (invalid_token('<', s, &i))
				return (2);
		}
		if (invalid_pipe(s, &i, i))
			return (2);
		if (invalid_quotes('"', s, &i) || invalid_quotes('\'', s, &i))
			return (2);
		i++;
	}
	return (0);
}
