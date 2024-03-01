/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:31:44 by paula             #+#    #+#             */
/*   Updated: 2024/03/01 11:39:19 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_dad_heredoc(int *exit_code, struct s_parse_heredoc *ph,
		t_dados *dados)
{
	*exit_code = ft_wait_exit_status(ph->child_pid);
	free((ph->red_temp)->filename);
	(ph->red_temp)->filename = ft_strdup("/tmp/heredoc");
	ft_init_signal();
	ph->red_temp = check_heredoc(&dados, &(ph->i));
}
