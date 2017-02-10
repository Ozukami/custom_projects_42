/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 10:48:38 by exam              #+#    #+#             */
/*   Updated: 2017/02/06 05:45:44 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		get_size(unsigned long value, unsigned long base)
{
	if (value < base)
		return (1);
	return (1 + get_size(value / base, base));
}

char	*ft_ultoa_base_2(long value, int base, int maj)
{
	char	*itoa;
	int		size;
	unsigned long	nb;

	nb = (unsigned long)value;
	size = get_size(nb, (unsigned long)base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	while (size >= 0)
	{
		if (nb % (unsigned long)base > 9 && maj)
			itoa[size--] = '7' + nb % (unsigned long)base;
		else if (nb % (unsigned long)base > 9)
			itoa[size--] = '7' + 32 + nb % (unsigned long)base;
		else
			itoa[size--] = '0' + nb % (unsigned long)base;
		nb = nb / (unsigned long)base;
	}
	return (itoa);
}
