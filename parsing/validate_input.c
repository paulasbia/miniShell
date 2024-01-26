/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:34 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/26 13:21:18 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_out_and_in(char *s)
{
	char	*n;

	n = "newline";
	s++;
	if (*s == '>')
	{
		if (*s == '>')
			s++;
	}
	else
	{
		if (*s == '<')
			s++;
	}
	while (*s != '\0' && (*s == ' ' || *s == '\t'))
		s++;
	if (*s == '>' || *s == '<' || *s == '|' || *s == '\0')
	{
		if (*s == '>' || *s == '<' || *s == '|')
			print_error_msg2("syntax error, command not found after token", *s);
		else
			print_error_msg("syntax error, command not found after token ", n);
		return (1);
	}
	return (0);
}

int	check_pipe(char *s)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
	{
		print_error_msg("|", "syntax error,command not found after pipe");
		return (1);
	}
	if (*s == '|')
	{
		print_error_msg("|", "syntax error near unexpected token `|'");
		return (1);
	}
	return (0);
}

int	check_dup_quotes(char *s)
{
	s++;
	while (*s != '"')
	{
		if (*s == '\0')
		{
			ft_putstr_fd("syntax error, open quotes\n", 1);
			return (1);
		}
		s++;
	}
	return (0);
}

int	validate_input(char *s)
{
	while (*s != '\0')
	{
		if (*s == '>' || *s == '<')
			return (check_out_and_in(s));
		if (*s == '|')
			return (check_pipe(s));
		if (*s == '"')
			return (check_dup_quotes(s));
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
			{
				if (*s == '\0')
				{
					ft_putstr_fd("syntax error, open quotes\n", 1);
					return (1);
				}
				s++;
			}
		}
		s++;
	}
	return (0);
}
