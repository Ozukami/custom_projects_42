/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 10:48:38 by exam              #+#    #+#             */
/*   Updated: 2017/05/29 00:49:48 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_size(long value, long base)
{
	if (value > -base && value <= -1)
		return (2);
	if (value >= 0 && value < base)
		return (1);
	if (value < -base)
		return (2 + get_size(-value / base, base));
	return (1 + get_size(value / base, base));
}

int		neg_case(long *nb, int base, char **itoa)
{
	if (*nb < 0 && base == 10)
	{
		*nb = -(*nb);
		itoa[0][0] = '-';
		return (1);
	}
	return (0);
}

char	*ft_itoa_base(int value, int base, int maj)
{
	char	*itoa;
	int		size;
	long	nb;
	int		neg;

	nb = (long)value;
	if (nb < 0 && base != 10)
		nb = UINT_MAX + 1 + value;
	size = get_size(nb, (long)base);
	if (!(itoa = ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	neg = neg_case(&nb, base, &itoa);
	while (size >= neg)
	{
		if (nb % (long)base > 9 && maj)
			itoa[size--] = '7' + nb % (long)base;
		else if (nb % (long)base > 9)
			itoa[size--] = '7' + 32 + nb % (long)base;
		else
			itoa[size--] = '0' + nb % (long)base;
		nb = nb / (long)base;
	}
	return (itoa);
}
