/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:34 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 12:27:50 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_input(char *s)
{
	while (*s != '\0')
	{
		if (*s == '>')
		{
			s++;
			if (*s == '>')
				s++;
			while (*s != '\0' && (*s == ' ' || *s == '\t'))
				s++;
			if (*s == '>' || *s == '<' || *s == '|' || *s == '\0')
			{
				ft_putstr_fd("syntax error, command not found after token\n",
					1);
				return (1);
			}
		}
		if (*s == '<')
		{
			s++;
			if (*s == '<')
				s++;
			while (*s != '\0' && (*s == ' ' || *s == '\t'))
				s++;
			if (*s == '>' || *s == '<' || *s == '|' || *s == '\0')
			{
				ft_putstr_fd("syntax error, command not found after token\n",
					1);
				return (1);
			}
		}
		if (*s == '|')
		{
			s++;
			while (*s == ' ' || *s == '\t')
			{
				s++;
			}
			if (*s == '\0')
			{
				ft_putstr_fd("syntax error, command not found after pipe\n", 1);
				return (1);
			}
			if (*s == '|')
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
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
					ft_putstr_fd("syntax error, open quotes\n", 1);
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