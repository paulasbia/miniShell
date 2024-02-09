/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2024/02/09 15:01:48 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_space_sign(const char **s, int *sign)
{
	const char	*str;

	str = *s;
	while (str && *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	*s = str;
}

long long int	ft_strtoull(const char *str)
{
	long long int	result;
	int				sign;
	int				digit;

	result = 0;
	sign = 1;
	ft_space_sign(&str, &sign);
	while (ft_isdigit((int)*str))
	{
		digit = *str - '0';
		if ((sign == 1 && result > (LLONG_MAX - digit) / 10))
		{
			result = LLONG_MAX;
			ft_exit_with_error("exit", "numeric argument required", 2);
		}
		if (sign == -1 && (-result) < (LLONG_MIN + digit) / 10)
		{
			result = LLONG_MIN;
			ft_exit_with_error("exit", "numeric argument required", 2);
		}
		result = result * 10 + digit;
		str++;
	}
	return ((result * sign) % 256);
}

int	ft_exit(t_dados *data, t_env **my_env)
{
	int	exit_status;

	rl_clear_history();
	ft_free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	if (!data || (!data->cmd[1] && data))
	{
		free_list(&data);
		exit(EXIT_SUCCESS);
	}
	if (data->cmd[2])
	{
		exit_status = ft_atoi(data->cmd[1]);
		ft_exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	if (!ft_isnumber(data->cmd[1]))
		ft_exit_with_error("exit", "numeric argument required", 2);
	else
		exit_status = ft_strtoull(data->cmd[1]);
	free_list(&data);
	exit(exit_status);
}
