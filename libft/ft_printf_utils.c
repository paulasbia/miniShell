/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-souz <pde-souz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:28 by pde-souz          #+#    #+#             */
/*   Updated: 2023/05/08 16:23:40 by pde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hexanbr_fd(unsigned int n, int fd, int x, long int *ret)
{
	int	digit;

	digit = n % 16;
	if (n >= 16)
	{
		ft_hexanbr_fd(n / 16, fd, x, ret);
	}
	if (digit <= 9)
	{
		digit = digit + 48;
		ft_putchar_pf_fd(digit, fd, ret);
	}
	else if (digit > 9 && x == 1)
	{
		digit = digit + 87;
		ft_putchar_pf_fd(digit, fd, ret);
	}
	else if (digit > 9 && x == 2)
	{
		digit = digit + 55;
		ft_putchar_pf_fd(digit, fd, ret);
	}
}

void	ft_print_pf(int n, int fd, long int *ret)
{
	int	digit;

	digit = n % 10;
	if (digit < 0)
	{
		digit = digit * -1;
	}
	if (n > 9 || n < -9)
	{
		ft_print_pf(n / 10, fd, ret);
	}
	digit = digit + 48;
	ft_putchar_pf_fd(digit, fd, ret);
}

void	ft_putnbr_pf_fd(int n, int fd, long int *ret)
{
	if (n < 0)
	{
		ft_putchar_pf_fd('-', fd, ret);
	}
	ft_print_pf(n, fd, ret);
}

void	ft_uniprint(unsigned int n, int fd, long int *ret)
{
	unsigned int	digit;

	digit = n % 10;
	if (n >= 10)
	{
		ft_uniprint(n / 10, fd, ret);
	}
	digit = digit + 48;
	ft_putchar_pf_fd(digit, fd, ret);
}

void	ft_adressp(unsigned long int n, int fd, long int *ret)
{
	int	digit;

	if (n == 0)
	{
		ft_putstr_pf_fd("(nil)", 1, ret);
	}
	if (n != 0)
	{
		digit = n % 16;
		if (n >= 16)
		{
			ft_adressp(n / 16, fd, ret);
		}
		if (digit <= 9)
		{
			digit = digit + 48;
			ft_putchar_pf_fd(digit, fd, ret);
		}
		else if (digit > 9)
		{
			digit = digit + 87;
			ft_putchar_pf_fd(digit, fd, ret);
		}
	}
}
