/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 09:23:54 by apoisson          #+#    #+#             */
/*   Updated: 2017/01/20 09:21:47 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_hex_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_print_hex_fd(-n, fd);
	}
	else if (n < 10)
		ft_putchar_fd('0' + n, fd);
	else if (n < 16)
		ft_putchar_fd('7' + n, fd);
	else
	{
		ft_print_hex_fd(n / 16, fd);
		if (n % 16 > 9)
			ft_putchar_fd('7' + n % 16, fd);
		else
			ft_putchar_fd('0' + n % 16, fd);
	}
}

void		ft_put_hex_fd(int n, int fd)
{
	long	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		ft_print_hex_fd(-l, fd);
	}
	else if (l < 10)
		ft_putchar_fd('0' + l, fd);
	else if (l < 16)
		ft_putchar_fd('7' + l, fd);
	else
	{
		ft_print_hex_fd(l / 16, fd);
		if (l % 16 > 9)
			ft_putchar_fd('7' + l % 16, fd);
		else
			ft_putchar_fd('0' + l % 16, fd);
	}
}

int			main(void)
{
	int	i;

	i = 0;
	while (i < 33)
	{
		ft_put_hex_fd(i, 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_put_hex_fd(255, 1);
	ft_putchar_fd('\n', 1);
	ft_put_hex_fd(-2147483648, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
