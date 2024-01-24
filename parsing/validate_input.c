/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:34 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 13:08:02 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_out_and_in(char *s)
{
    s++;
	if (*s == '>')
	{
		if (*s == '>')
			s++;
		while (*s != '\0' && (*s == ' ' || *s == '\t'))
			s++;
		if (*s == '>' || *s == '<' || *s == '|' || *s == '\0')
		{
			print_error_msg(s, "syntax error, command not found after token");
			return (1);
		}
	}
	else
	{
		if (*s == '<')
			s++;
		while (*s != '\0' && (*s == ' ' || *s == '\t'))
			s++;
		if (*s == '>' || *s == '<' || *s == '|' || *s == '\0')
		{
			print_error_msg(s, "syntax error, command not found after token");
			return (1);
		}
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
		{
			s++;
			while (*s == ' ' || *s == '\t')
			{
				s++;
			}
			if (*s == '\0')
			{
				print_error_msg(s, "syntax error,command not found after pipe");
				return (1);
			}
			if (*s == '|')
			{
				print_error_msg(s, "syntax error near unexpected token `|'");
				return (1);
			}
		}
		if (*s == '"')
		{
			s++;
			while (*s != '"')
			{
				if (*s == '\0')
				{
					print_error_msg(s, "syntax error, open quotes");
					return (1);
				}
				s++;
			}
		}
		if (*s == '\'')
		{
			s++;
			while (*s != '\'')
			{
				if (*s == '\0')
				{
					print_error_msg(s, "syntax error, open quotes");
					return (1);
				}
				s++;
			}
		}
		s++;
	}
	return (0);
}
