/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:41 by ricardo           #+#    #+#             */
/*   Updated: 2024/01/24 10:51:53 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_dp(char **split)
{
    int i = 0;
    while (split[i] != NULL) 
    {
        free(split[i]);
        split[i] = NULL;
        i++;
    }
    free(split);
    split = NULL;
}
void free_list(t_dados **lst) 
{
    t_dados *temp;
    while (*lst != NULL) 
    {
        temp = *lst;
        *lst = (*lst)->next;
        free_dp(temp->comando);
        while(temp->nbr_redirections > 0)
        {
            free(temp->redirect[temp->nbr_redirections - 1].filename);
            temp->nbr_redirections--;            
        }
        free(temp->redirect);
        free(temp);
        temp = NULL;
    }
    free(*lst);
    *lst = NULL;
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
