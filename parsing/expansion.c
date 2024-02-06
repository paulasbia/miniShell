/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:35:21 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/06 21:01:51 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_chars_env(char c)
{
    if (c == 95 || c == 29 || c == 28)
        return 0;
    if ((c >= 48  && c <= 57 ) || (c >= 65 && c <= 90) ||  (c >= 97  && c <= 122))
        return 0;
    return (1);
}

int	find_char(char *s, char c)
{
    int i = 0;
	while (c != s[i])
	{
		if (s[i] == 0)
		{
			return (-1);
		}
		i++;
	}
    return (i);
}

char  *change_input(char *cmd_input, char *key, int size_index_env)
{
    char *result;
    int i = 0; 
    int j = 0;
    int x = size_index_env + 1; //4
    int total_size = ft_strlen(cmd_input); //11
    int size_env = ft_strlen(key) - x; //3
    int malloc_size = total_size + size_env - x;

    printf("s_index_env: %d\n", size_index_env);
    printf("total size: %d\n", total_size);
    printf("env size: %d\n", size_env);
    printf("malloc size: %d\n", malloc_size);
    printf("x size: %d\n", x);

    result = malloc(sizeof(char)*(malloc_size + 1));
    
    while(cmd_input[i] != '\0' && cmd_input[i] != '$')
    {
        result[j] = cmd_input[i];
        i++;
        j++;
    }
    while(key[x] != '\0')
    {
        result[j] = key[x];
        j++;
        x++;   
    }
    i = i + size_index_env + 1;
    while(cmd_input[i] != '\0')
    {
        result[j] = cmd_input[i];
        i++;
        j++;
    }
    result[j] = '\0';
    free(cmd_input);
    return(result);
}

char  *change_exit(char *cmd_input, char *exit_status, int size)
{
    char *result;
    int i = 0; 
    int j = 0;
    int x = 0;
    int total_size = ft_strlen(cmd_input); //2
    int malloc_size = total_size - size + ft_strlen(exit_status); 

    printf("total size: %d\n", total_size);
    printf("malloc size: %d\n", malloc_size);

    result = malloc(sizeof(char)*(malloc_size + 1));
    
    while(cmd_input[i] != '\0' && cmd_input[i] != '$')
    {
        result[j] = cmd_input[i];
        i++;
        j++;
    }
    while(exit_status[x] != '\0')
    {
        result[j] = exit_status[x];
        j++;
        x++;   
    }
    i += size;
    while(cmd_input[i] != '\0')
    {
        result[j] = cmd_input[i];
        i++;
        j++;
    }
    result[j] = '\0';
    free(cmd_input); 
    return(result);
}


int expansion(t_dados *node, t_env *env, int exit_status)
{
	int i = 0;
    int j = 0;
    char *env_input;
    t_env *tmp_l_env;
    int start = 0;
    int flag = 0;
    int index = 0;
    char *string_exit;
    tmp_l_env = env;
	while(node->comando[i] != NULL)
	{
		j = 0;
		while(node->comando[i][j] != '\0')
		{
            if(node->comando[i][j] == '"')
            {
                flag = 1;
                
            }
            if(node->comando[i][j] == '\'' && flag == 0)
            {   
                j++;
                while(node->comando[i][j] != '\'')
                    j++;
            }
			if(node->comando[i][j] == '$')
			{
                j++;
				while(node->comando[i][j] == '$') 
                   j++;
                if(node->comando[i][j] == '?')
                {
                    string_exit = ft_itoa(exit_status);
                    node->comando[i] = change_exit(node->comando[i], string_exit, 2);
                    free(string_exit);
                    continue ;
                }
                start  = j;
                //while(node->comando[i][j] != '\0' && node->comando[i][j] != ' ' && node->comando[i][j] != '\t')
                while(node->comando[i][j] != '\0' && node->comando[i][j] != ' ' && node->comando[i][j] != '\t' && validate_chars_env(node->comando[i][j]) == 0)
                {
                    j++;
                }
                
                env_input = ft_substr(node->comando[i], start, (j - start));
                while(tmp_l_env != NULL)
                {
                   index = find_char(tmp_l_env->key, '=');
                    if((size_t)index == ft_strlen(env_input))
                    {
                        if(ft_strncmp(tmp_l_env->key, env_input, ft_strlen(env_input)) == 0)
                        {
                            node->comando[i] = change_input(node->comando[i], tmp_l_env->key, index);
                            break ;
                        }
                    }
                    tmp_l_env = tmp_l_env->next;            
                }
                if(tmp_l_env == NULL)
                {
                    node->comando[i] = change_exit(node->comando[i], "", (j - start + 1));
                }
                free(env_input);
			}
            if (node->comando[i][j] != '\0')
			    j++;
		}        
		i++;
	}
    return (0);
}
