/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/23 14:03:00 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void free_list(t_dados *lst) 
{
    t_dados *temp;
    while (lst != NULL) {
        temp = lst;
        lst = lst->next;
        free(temp->comando);
        free(temp);
    }
}

void free_cmd(char **split)
{
    int i = 0;
    while (split[i] != NULL) {
        free(split[i]);
        i++;
    }
    free(split);
}

char *clean_quotes(char *s)
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
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
			{
                size++;
				i++;			
			}
        }
        i++;
        size++;
    }
    printf("%d\n", size);
    printf("%s\n", s);
    i = 0;
    new_string =  malloc ((sizeof(char) * size) + 1);
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
        else if(s[i] == '"')
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
    new_string[j] = '\0';
    return (new_string);
}
