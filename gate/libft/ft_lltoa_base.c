/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:22:05 by qumaujea          #+#    #+#             */
/*   Updated: 2017/02/02 11:57:05 by apoisson         ###   ########.fr       */
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

char			*ft_lltoa_base(long long value, int base, int maj)
{
	char		*itoa;
	int			size;
	int			neg;

	if (value == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (value < 0 && base != 10)
		value = 4294967296 + value;
	size = get_size(value, (long long)base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	neg = neg_case(&value, base, &itoa);
	while (size >= neg)
	{
		if (value % (long long)base > 9 && maj)
			itoa[size--] = '7' + value % (long long)base;
		else if (value % (long long)base > 9)
			itoa[size--] = '7' + 32 + value % (long long)base;
		else
			itoa[size--] = '0' + value % (long long)base;
		value = value / (long long)base;
	}
	return (itoa);
}
