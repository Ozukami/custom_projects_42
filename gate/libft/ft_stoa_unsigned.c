/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 12:11:22 by apoisson          #+#    #+#             */
/*   Updated: 2017/01/24 09:56:40 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_size(unsigned short value)
{
	if (value < 10)
		return (1);
	return (1 + get_size(value / 10));
}

char		*ft_stoa_unsigned(short value)
{
	char			*itoa;
	int				size;
	unsigned short	nb;

	nb = (unsigned short)value;
	size = get_size(nb);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	while (size >= 0)
	{
		itoa[size--] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (itoa);
}
