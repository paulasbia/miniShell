/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:52:28 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/01 20:22:53 by ricardo          ###   ########.fr       */
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


char **clear_dp_quotes(char **split_cmd)
{
	int i = 0;
	char *new;

	new = NULL;	
	while (split_cmd[i] != NULL)
	{
		new = clean_quotes(split_cmd[i]);
		free(split_cmd[i]);
		split_cmd[i] = new;
		i++;
	}
	return (split_cmd);
}

t_dados	*ft_lstnew_p(int n_reds, int n_cmd, char **split_cmd)
{
	t_dados	*node;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	node = (t_dados *)malloc(sizeof(t_dados)); // aloco memoria para meu node
	if (!node)
		return (NULL);
	node->comando = malloc(sizeof(char *) * (n_cmd + 1));      
		// aloco memoria para o tanto de cmd que tenho
	node->redirect = malloc(sizeof(t_redirect) * (n_reds + 1));
		// e tbm para o n de redireções
	while (split_cmd[i] != NULL)
	{
		if (redirection(split_cmd[i]) != -1)
		// se minha redirection for diferente de -1 é pq  há alguma redireção
		{
			node->redirect[j].redirect_type = redirection(split_cmd[i]);
			// eu guardo o tipo e o nome
			node->redirect[j++].filename = ft_strdup(split_cmd[i + 1]);
			i += 2; // ando duas pq depois da redirecao sempre tem o arquivo
		}
		else
		{
			node->comando[x++] = ft_strdup(split_cmd[i++]);
				// se n for redirecao ou filename é comando.
		}
	}
	node->nbr_redirections = n_reds;
		// salvo o n de red para paula saber qnts há.
	node->comando[x] = NULL;
	node->comando = clear_dp_quotes(node->comando);
	int z = 0;
	char *new;
	while (z < node->nbr_redirections)
	{
		new = clean_quotes(node->redirect[i].filename);
		free(node->redirect[i].filename);
		node->redirect[i].filename = new;
		i++;
	}
	node->next = NULL;
	free_dp(split_cmd);
	return (node);
}

void	alocacao(t_dados **dados_head, int redirection, int cmd,
		char **split_cmd) // aqui tbm
{
	t_dados *node;
	node = ft_lstnew_p(redirection, cmd, split_cmd);
	ms_lstadd_back(dados_head, node);
}

t_dados	*parsing(char *input)
{
	char	**s_pipe;
	char	**split_cmd;
	int		i;
	int		j;
	int		nbr_redirections;
	int		nbr_comands;
	t_dados	*dados_head;

	i = 0;
	j = 0;
	nbr_redirections = 0;
	nbr_comands = 0;
	dados_head = NULL;
	s_pipe = split_pipe(input);
	while (s_pipe[i] != NULL)
	{
		split_cmd = split_ms(s_pipe[i]);
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
				j += 2;
			}
			else
			{
				nbr_comands++;
				j++;
			}
		}
		alocacao(&dados_head, nbr_redirections, nbr_comands, split_cmd);
		i++;
	}
	free_dp(s_pipe);
	//	print_list(dados_head);
	return (dados_head);
}
