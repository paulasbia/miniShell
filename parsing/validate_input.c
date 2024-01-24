/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:34 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 10:57:36 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_input(char *s)
{
    int	i;

	i = 0;
	while (s[i] != '\0')
	{
        if(s[i] == '>')
        {
            i++;
            if(s[i] ==  '>')
                i++;
            while(s[i] != '\0' && (s[i] == ' ' || s[i] == '\t')) 
                i++;
            if(s[i] == '>' || s[i] == '<' || s[i] == '|'  || s[i] == '\0')
            {
                ft_putstr_fd("syntax error, command not found after token\n", 1);
                return (1);
            }
        }
        if(s[i] == '<')
        {
            i++;
            if(s[i] ==  '<')
                i++;
            while(s[i] != '\0' && (s[i] == ' ' || s[i] == '\t')) 
                i++;
            if(s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '\0')
            {
                ft_putstr_fd("syntax error, command not found after token\n", 1);
                return (1);
            }
        }
        if(s[i] == '|')
        {
            i++;
             while(s[i] == ' ' || s[i] == '\t')
            {
                i++;			
            }
            if(s[i] == '\0')
            {
                ft_putstr_fd("syntax error, command not found after pipe\n", 1);
                return (1);
            } 
            if (s[i] == '|')
            {
                ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
                return (1);
            }    
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
            {
                if(s[i] == '\0')
                {
                    ft_putstr_fd("syntax error, open quotes\n", 1);
                    return (1);
                }
                i++;
            }    
        }
        if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
            {
                if(s[i] == '\0')
                {
                    ft_putstr_fd("syntax error, open quotes\n", 1);
                    return (1);
                }
                i++;
            }    
        }
		i++;
	}
    return (0);
}