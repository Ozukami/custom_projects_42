/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 10:48:38 by exam              #+#    #+#             */
/*   Updated: 2017/02/06 05:43:30 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		get_size(long long value, long long base)
{
	if (value > -base && value <= -1)
		return (2);
	if (value >= 0 && value < base)
		return (1);
	if (value < -base)
		return (2 + get_size(-value / base, base));
	return (1 + get_size(value / base, base));
}

static int		neg_case(long long *nb, int base, char **itoa)
{
	if (*nb < 0 && base == 10)
	{
		*nb = -(*nb);
		itoa[0][0] = '-';
		return (1);
	}
	return (0);
}

char	*ft_ultoa_base(long value, int base, int maj)
{
	char	*itoa;
	int		size;
	long long	nb;
	int		neg;

	nb = (long long)value;
	if (nb < 0 && base != 10)
		nb = UINT_MAX + 1 + value;
	if (value == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	size = get_size(nb, (long long)base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	neg = neg_case(&nb, base, &itoa);
	while (size >= neg)
	{
		if (nb % (long long)base > 9 && maj)
			itoa[size--] = '7' + nb % (long long)base;
		else if (nb % (long long)base > 9)
			itoa[size--] = '7' + 32 + nb % (long long)base;
		else
			itoa[size--] = '0' + nb % (long long)base;
		nb = nb / (long long)base;
	}
	return (itoa);
}
