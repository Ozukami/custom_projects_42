/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:26:08 by qumaujea          #+#    #+#             */
/*   Updated: 2017/02/06 02:29:03 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(int value, int base)
{
	if (value > -base && value <= -1)
		return (2);
	if (value >= 0 && value < base)
		return (1);
	if (value < -base)
		return (2 + get_size(-value / base, base));
	return (1 + get_size(value / base, base));
}

static int		neg_case(int *nb, int base, char **itoa)
{
	if (*nb < 0 && base == 10)
	{
		*nb = -(*nb);
		itoa[0][0] = '-';
		return (1);
	}
	return (0);
}

char			*ft_stoa_base(short value, int base, int maj)
{
	char		*itoa;
	int			size;
	int			nb;
	int			neg;

	nb = (int)value;
	if (nb < 0 && base != 10)
		nb = USHRT_MAX + value + 1;
	size = get_size(nb, base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	neg = neg_case(&nb, base, &itoa);
	while (size >= neg)
	{
		if (nb % base > 9 && maj)
			itoa[size--] = '7' + nb % base;
		else if (nb % base > 9)
			itoa[size--] = '7' + 32 + nb % base;
		else
			itoa[size--] = '0' + nb % base;
		nb = nb / base;
	}
	return (itoa);
}
