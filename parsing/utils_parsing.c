/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:22:23 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 14:06:30 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
