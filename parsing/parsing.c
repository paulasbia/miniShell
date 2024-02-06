/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:52:28 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/06 15:38:13 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
// 		printf("num red: %d\n", temp->nbr_redirections);
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
// 			printf("o comando eh %s\n\n", temp->comando[j]);
// 			j++;
// 		}
// 		temp = temp->next;
// 	}
// }

t_dados	*ft_lstnew_p(int n_reds, int n_cmd, char **split_cmd, int x)
{
	t_dados	*node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	node = (t_dados *)malloc(sizeof(t_dados));
	node->comando = malloc(sizeof(char *) * (n_cmd + 1));
	node->redirect = malloc(sizeof(t_redirect) * (n_reds + 1));
	while (split_cmd[i] != NULL)
	{
		if (redirection(split_cmd[i]) != -1)
		{
			node->redirect[j].redirect_type = redirection(split_cmd[i]);
			node->redirect[j++].filename = ft_strdup(split_cmd[i + 1]);
			i += 2;
		}
		else
			node->comando[x++] = ft_strdup(split_cmd[i++]);
	}
	node->nbr_redirections = n_reds;
	node->comando[x] = NULL;
	handle_clean_quotes(node, split_cmd);
	node->next = NULL;
	return (node);
}

void	handle_parsing_split(char *s_pipe, t_dados **dados_head)
{
	int		j;
	int		nbr_redirections;
	int		nbr_comands;
	char	**split_cmd;
	t_dados	*node;

	split_cmd = split_ms(s_pipe);
	j = 0;
	nbr_redirections = 0;
	nbr_comands = 0;
	while (split_cmd[j] != NULL)
	{
		if (redirection(split_cmd[j]) != -1)
		{
			nbr_redirections++;
			if (split_cmd[j + 1] == NULL)
				break ;
			j++;
		}
		else
			nbr_comands++;
		j++;
	}
	node = ft_lstnew_p(nbr_redirections, nbr_comands, split_cmd, 0);
	ms_lstadd_back(dados_head, node);
}

t_dados	*parsing(char *input)
{
	char	**s_pipe;
	int		i;
	t_dados	*dados_head;

	i = 0;
	dados_head = NULL;
	s_pipe = split_pipe(input);
	while (s_pipe[i] != NULL)
	{
		handle_parsing_split(s_pipe[i], &dados_head);
		i++;
	}
	free_dp(s_pipe);
	return (dados_head);
}
