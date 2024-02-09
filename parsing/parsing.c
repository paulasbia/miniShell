/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:52:28 by ricardo           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/05 20:19:09 by ricardo          ###   ########.fr       */
=======
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
>>>>>>> f667816e2593fb8d061182e1f549c6b5f858f640
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
int	redirection(char *red)
{
	if (ft_strncmp("<<", red, 2) == 0)
		return (2);
	else if (ft_strncmp(">>", red, 2) == 0)
		return (3);
	else if (ft_strncmp(">", red, 1) == 0)
		return (0);
	else if (ft_strncmp("<", red, 1) == 0)
		return (1);
	else
		return (-1);
}

void	ms_lstadd_back(t_dados **lst, t_dados *node)
{
	t_dados	*temp;

	temp = *lst;
	if (*lst == NULL)
		*lst = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

// void	print_list(t_dados *lst)
// {
// 	int		i;
// 	int		j;
// 	t_dados	*temp;

// 	i = 0;
// 	j = 0;
// 	temp = lst;
// 	while (temp != NULL)
// 	{
// 		printf("redireçao:\n");
// 		i = 0;
// 		while (i < temp->nbr_redirections)
// 		{
// 			printf("%s\n", temp->redirect[i].filename);
// 			printf("%d\n", temp->redirect[i].redirect_type);
// 			i++;
// 		}
// 		j = 0;
// 		printf("comandos:\n");
// 		while (temp->comando[j] != NULL)
// 		{
// 			printf("%s\n", temp->comando[j]);
// 			j++;
// 		}
// 		temp = temp->next;
// 	}
// }

t_dados	*ft_lstnew_p(int n_reds, int n_cmd, char **split_cmd, int x)
=======
t_dados	*alloc_nodes(int n_reds, int n_cmd)
>>>>>>> f667816e2593fb8d061182e1f549c6b5f858f640
{
	t_dados	*node;

	node = (t_dados *)malloc(sizeof(t_dados));
	node->cmd = malloc(sizeof(char *) * (n_cmd + 1));
	node->redirect = malloc(sizeof(t_redirect) * (n_reds + 1));
	return (node);
}

t_dados	*ft_lstnew_p(char **split_cmd, t_env *env, int exit, t_dados *node)
{
	t_int_parsing	ip;

	ip.x = 0;
	ip.i = 0;
	ip.j = 0;
	ip.nbr_reds = 0;
	while (split_cmd[ip.i] != NULL)
	{
		if (redirection(split_cmd[ip.i]) != -1)
		{
			node->redirect[ip.j].redirect_type = redirection(split_cmd[ip.i]);
			node->redirect[ip.j++].filename = ft_strdup(split_cmd[ip.i + 1]);
			ip.nbr_reds++;
			ip.i += 2;
		}
		else
			node->cmd[ip.x++] = ft_strdup(split_cmd[ip.i++]);
	}
	node->nbr_redirections = ip.nbr_reds;
	node->cmd[ip.x] = NULL;
	expansion(node, env, exit);
	handle_clean_quotes(node, split_cmd);
	node->next = NULL;
	return (node);
}

void	handle_parsing_split(char *s_pipe, t_dados **dados_head, t_env *env,
		int exit)
{
	t_int_parsing	ip;
	char			**split_cmd;
	t_dados			*node;

	split_cmd = split_ms(s_pipe);
	ip.j = 0;
	ip.nbr_reds = 0;
	ip.nbr_cmd = 0;
	while (split_cmd[ip.j] != NULL)
	{
		if (redirection(split_cmd[ip.j]) != -1)
		{
			ip.nbr_reds++;
			if (split_cmd[ip.j + 1] == NULL)
				break ;
			ip.j++;
		}
		else
			ip.nbr_cmd++;
		ip.j++;
	}
	node = alloc_nodes(ip.nbr_reds, ip.nbr_cmd);
	node = ft_lstnew_p(split_cmd, env, exit, node);
	ms_lstadd_back(dados_head, node);
}

t_dados	*parsing(char *input, t_env *env, int exit)
{
	char	**s_pipe;
	int		i;
	t_dados	*dados_head;

	i = 0;
	dados_head = NULL;
	s_pipe = split_pipe(input);
	while (s_pipe[i] != NULL)
	{
		handle_parsing_split(s_pipe[i], &dados_head, env, exit);
		i++;
	}
	free_dp(s_pipe);
	return (dados_head);
}
