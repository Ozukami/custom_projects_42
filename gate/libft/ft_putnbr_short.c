/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_short.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:09:00 by apoisson          #+#    #+#             */
/*   Updated: 2016/12/15 11:18:51 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_short(short n)
{
	if (n == SHRT_MIN)
		ft_putstr("-32768");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr_short(-n);
	}
	else if (n < 10)
		ft_putchar('0' + n);
	else
	{
		ft_putnbr_short(n / 10);
		ft_putchar('0' + n % 10);
	}
}
