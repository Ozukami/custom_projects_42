/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 10:05:38 by apoisson          #+#    #+#             */
/*   Updated: 2016/12/15 11:18:33 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_long(long n)
{
	if (n == LONG_MIN)
		ft_putstr("-9223372036854775808");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr_long(-n);
	}
	else if (n < 10)
		ft_putchar('0' + n);
	else
	{
		ft_putnbr_long(n / 10);
		ft_putchar('0' + n % 10);
	}
}
