/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 10:48:38 by exam              #+#    #+#             */
/*   Updated: 2017/02/06 06:34:31 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		get_size(unsigned char value, unsigned char base)
{
	if (value < base)
		return (1);
	return (1 + get_size(value / base, base));
}

char	*ft_usstoa_base(int value, int base, int maj)
{
	char			*itoa;
	int				size;
	unsigned char	nb;

	nb = (unsigned char)value;
	size = get_size(nb, (unsigned char)base);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	while (size >= 0)
	{
		if (nb % (unsigned char)base > 9 && maj)
			itoa[size--] = '7' + nb % (unsigned char)base;
		else if (nb % (unsigned char)base > 9)
			itoa[size--] = '7' + 32 + nb % (unsigned char)base;
		else
			itoa[size--] = '0' + nb % (unsigned char)base;
		nb = nb / (unsigned char)base;
	}
	return (itoa);
}
