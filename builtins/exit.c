/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:23:00 by paula             #+#    #+#             */
/*   Updated: 2024/02/04 11:05:55 by paula            ###   ########.fr       */
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

int	ft_exittoi(char *str)
{
	int				i;
	int				sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	//printf("%s\n", str);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str) > 20 || !ft_isnumber(str + i))
		ft_exit_with_error("exit", "numeric argument required", 2);
	result = 0;
	while (str[i])
	{
		if (result != 0 && ULLONG_MAX/result){
			printf("MULTI %llu\n", ULLONG_MAX/result);	
		}
		if (result != 0 && ULLONG_MAX/result <10){
			ft_exit_with_error("exit", "numeric argument required", 2);
		}
		result = (result * 10);
		if (ULLONG_MAX - result <= (unsigned long long) (str[i] - '0')){
			ft_exit_with_error("exit", "numeric argument required", 2);
		}
		result = result + (str[i] - '0');
		//printf("result AGORA eh %llu\n", result);
		i++;
	}
	return ((result * sign) % 256);
}

int	ft_exit(t_dados *data, t_env **my_env)
{
	int	exit_status;

	rl_clear_history();
	ft_free_env(my_env);
	ft_putstr_fd("exit\n", 1);
	if (!data || (!data->comando[1] && data))
	{
		free_list(&data);
		exit(EXIT_SUCCESS);
	}
	if (data->comando[2] && ft_isnumber(data->comando[1]))
	{
		exit_status = ft_atoi(data->comando[1]);
		ft_exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
	else
		exit_status = ft_exittoi(data->comando[1]);
	free_list(&data);
	exit(exit_status);
}
