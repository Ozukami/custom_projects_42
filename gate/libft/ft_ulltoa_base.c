/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:22:05 by qumaujea          #+#    #+#             */
/*   Updated: 2017/02/02 11:58:46 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		get_size(unsigned long long value, unsigned long long base)
{
	if (value < base)
		return (1);
	return (1 + get_size(value / base, base));
}

char			*ft_ulltoa_base(unsigned long long value, int base, int maj)
{
	char		*itoa;
	int			size;

	size = get_size(value, (unsigned long long)base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	while (size >= 0)
	{
		if (value % (unsigned long long)base > 9 && maj)
			itoa[size--] = '7' + value % (unsigned long long)base;
		else if (value % (unsigned long long)base > 9)
			itoa[size--] = '7' + 32 + value % (unsigned long long)base;
		else
			itoa[size--] = '0' + value % (unsigned long long)base;
		value = value / (unsigned long long)base;
	}
	return (itoa);
}
