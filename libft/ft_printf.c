/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-souz <pde-souz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:01:54 by pde-souz          #+#    #+#             */
/*   Updated: 2023/05/08 19:51:01 by pde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putchar_pf_fd(char c, int fd, long int *ret)
{
	write(fd, &c, 1);
	*ret = *ret + 1;
}

void	ft_putstr_pf_fd(char *s, int fd, long int *ret)
{
	if (s == 0)
	{
		ft_putstr_pf_fd("(null)", fd, ret);
		return ;
	}
	while (*s)
		ft_putchar_pf_fd(*s++, fd, ret);
}

void	replace(char st, va_list ap, long int *ret)
{
	unsigned long int	arg;

	if (st == '%')
		ft_putchar_pf_fd(st, 1, ret);
	if (st == 'c')
		ft_putchar_pf_fd(va_arg(ap, int), 1, ret);
	if (st == 's')
		ft_putstr_pf_fd(va_arg(ap, char *), 1, ret);
	if (st == 'd' || st == 'i')
		ft_putnbr_pf_fd(va_arg(ap, int), 1, ret);
	if (st == 'u')
		ft_uniprint(va_arg(ap, int), 1, ret);
	if (st == 'x')
		ft_hexanbr_fd(va_arg(ap, int), 1, 1, ret);
	if (st == 'X')
		ft_hexanbr_fd(va_arg(ap, int), 1, 2, ret);
	if (st == 'p')
	{
		arg = va_arg(ap, unsigned long int);
		if (arg != 0)
		{
			ft_putstr_pf_fd("0x", 1, ret);
		}
		ft_adressp(arg, 1, ret);
	}
}

int	ft_printf(const char *st, ...)
{
	long int	ret;
	int			i;
	va_list		ap;

	ret = 0;
	i = 0;
	va_start(ap, st);
	while (st[i] != 0)
	{
		if (st[i] == '%')
		{
			replace(st[++i], ap, &ret);
		}
		else
			ret = ret + write(1, &st[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}
