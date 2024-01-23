/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/23 10:31:47 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

char *clean_quotes(char *s) //aonde enfiar essa função de bosta?? 
{   
    int i = 0;
    int size = 0;
    int j = 0;
    char *new_string;

    while(s[i] != '\0')
    {
        if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
			{
				size++;
                i++;			
			}
            i++;
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
			{
                size++;
				i++;			
			}
            i++;
        }
        else
        {
            i++;
            size++;
        }
    }
    i = 0;
    new_string =  malloc (sizeof(char) * size);
    while(s[i] != '\0')
    {
         if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
			{
                new_string[j] = s[i];
                i++;
                j++;			
			}
            i++;
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
			{
                new_string[j] = s[i];
                i++;
                j++;		
			}
            i++;
        }
        else
        {
            new_string[j] = s[i];
            j++;
            i++;
        }
    }
    return (new_string);
}
