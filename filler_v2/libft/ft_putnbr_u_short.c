/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_short.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:07:02 by apoisson          #+#    #+#             */
/*   Updated: 2016/12/15 11:19:07 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_u_short(unsigned short n)
{
	if (n < 10)
		ft_putchar('0' + n);
	else
	{
		ft_putnbr_u_short(n / 10);
		ft_putchar('0' + n % 10);
	}
}
