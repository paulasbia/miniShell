/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:35:21 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/07 18:36:37 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_chars_env(char c)
{
	if (c == 95 || c == 29 || c == 28)
		return (0);
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (0);
	return (1);
}

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (c != s[i])
	{
		if (s[i] == 0)
			return (-1);
		i++;
	}
	return (i);
}

char	*change_input(char *cmd_input, char *key, int size_index_env) 
{
	char	*result;
	int		i;
	int		j;
	int		malloc_size;
    int     x;
    int     total_size;
    int     size_env;
    
	i = 0;
	j = 0;
	x = size_index_env + 1;            
	total_size = ft_strlen(cmd_input);
	size_env = (int)ft_strlen(key) - x;     
	malloc_size = total_size + size_env - x;
	result = malloc(sizeof(char) * (malloc_size + 1));
	while (cmd_input[i] != '\0' && cmd_input[i] != '$')
	{
		result[j] = cmd_input[i];
		i++;
		j++;
	}
	while (key[x] != '\0')
	{
		result[j] = key[x];
		j++;
		x++;
	}
	i = i + size_index_env + 1;
	while (cmd_input[i] != '\0')
	{
		result[j] = cmd_input[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(cmd_input);
	return (result);
}

char	*change_exit(char *cmd_input, char *exit_status, int size)
{
	char	*result;
	int		i;
	int		j;
	int		x;
	int		malloc_size;

	i = 0;
	j = 0;
	x = 0;
	int total_size = ft_strlen(cmd_input);
	malloc_size = total_size - size + ft_strlen(exit_status);
	result = malloc(sizeof(char) * (malloc_size + 1));
	while (cmd_input[i] != '\0' && cmd_input[i] != '$')
	{
		result[j] = cmd_input[i];
		i++;
		j++;
	}
	while (exit_status[x] != '\0')
	{
		result[j] = exit_status[x];
		j++;
		x++;
	}
	i += size;
	while (cmd_input[i] != '\0')
	{
		result[j] = cmd_input[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(cmd_input);
	return (result);
}

int	find_exception(char *cmd_input, int j)
{
	j++;
	if (cmd_input[j] == '"' || cmd_input[j] == '\'')
		return (1);
	if (cmd_input[j] == '\0' || cmd_input[j] == ' ' || cmd_input[j] == '\t')
		return (1);
	return (0);
}

void	move_empty_command(char **comando, int i)
{
  //  char *tmp;
    // int help = 0;

//    tmp = comando[i];

    // while (comando[i])
    // {
    //     printf("%i: %s\n", i, comando[i]);
    //     i++;
    // }
    
    // while(comando[i] != NULL || help == 0)
    // {
    //     comando[i] = comando[i + 1];
    //     printf("%s\n", comando[i]);
    //     help = 1;
    //     i++;
    // }
//     printf("entrou\n");
// 	while (comando[i] != NULL)
// 	{
// 		if (ft_strncmp(comando[i], NULL, 1) == 0)
//         {
// 			free(comando[i]);
//             int j = i;
//             while (comando[j] != NULL)
//             {
//                 comando[j]= comando[j + 1];
//                 j++;
//             }
//             i = 0;
//         }
// 		else
// 		    i++;
// 	}
//     comando[i] = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//                     REFATORAÇÃO EM ANDAMENTO
/////////////////////////////////////////////////////////////////////////////////////////
// void find_quotes_(int *i, int *j, char **comando, int exit_status)
// {
//     if (comando[*i][*j] == '$')
//     {
//         if (find_exception(comando[*i], *j) == 1)
//             break ;
//         (*j)++;
//         while (comando[*i][*j] == '$')
//             (*j)++;
//         if (comando[*i][*j] == '?')
//         {
//             string_exit = ft_itoa(exit_status);
//             comando[*i] = change_exit(comando[*i], string_exit, 2);
//             free(string_exit);
//             continue ;
//         }
//     }
// }

int	expansion(t_dados *node, t_env *env, int exit_status)
{
	int		i;
	int		j;
	char	*env_input;
	t_env	*tmp_l_env;
	int		start;
	int		flag;
	int		index;
	char	*string_exit;
    
	i = 0;
	j = 0;
	start = 0;
	flag = 0;
	index = 0;
	tmp_l_env = env;
	while (node->comando[i] != NULL)
	{
		j = 0;
		while (node->comando[i][j] != '\0')
		{
			if (node->comando[i][j] == '"')
				flag = 1;
			if (node->comando[i][j] == '\'' && flag == 0)
			{
				j++;
				while (node->comando[i][j] != '\'')
					j++;
			}
			if (node->comando[i][j] == '$')
			{
				if (find_exception(node->comando[i], j) == 1)
					break ;
				j++;
				while (node->comando[i][j] == '$')
					j++;
				if (node->comando[i][j] == '?')
				{
					string_exit = ft_itoa(exit_status);
					node->comando[i] = change_exit(node->comando[i], string_exit, 2);
					free(string_exit);
					continue ;
				}
				start = j;
				while (node->comando[i][j] != '\0' && node->comando[i][j] != ' ' && node->comando[i][j] != '\t' && validate_chars_env(node->comando[i][j]) == 0)
					j++;
				env_input = ft_substr(node->comando[i], start, (j - start));
				while (tmp_l_env != NULL)
				{
					index = find_char(tmp_l_env->key, '=');
					if ((size_t)index == ft_strlen(env_input))
					{
						if (ft_strncmp(tmp_l_env->key, env_input,
								ft_strlen(env_input)) == 0)
						{
							node->comando[i] = change_input(node->comando[i],
								tmp_l_env->key, index);
							break ;
						}
					}
					tmp_l_env = tmp_l_env->next;
				}
				if (tmp_l_env == NULL)
				{
			        free(node->comando[i]);
					node->comando[i] = NULL;
                    move_empty_command(node->comando, i);
                    i--;
                    break ;
					//help = 1;
				}
				//free(env_input);
                //free(tmp_l_env);
			}
           // printf("Length %ld\n", ft_strlen(node->comando[i]));
			if ( node->comando[i][j] != '\0')
				j++;
		}
		i++;
	}
    // if(help == 1)
	//     move_empty_command(node);
	return (0);
}
