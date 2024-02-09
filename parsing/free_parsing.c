/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:01:12 by ricardo           #+#    #+#             */
/*   Updated: 2024/02/08 20:29:13 by ricardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_dp(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_list(t_dados **lst)
{
	t_dados	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free_dp(temp->cmd);
		while (temp->nbr_redirections > 0)
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
