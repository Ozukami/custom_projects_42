/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 09:53:54 by qumaujea          #+#    #+#             */
/*   Updated: 2017/01/24 09:54:07 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_size(unsigned long long int value)
{
	if (value < 10)
		return (1);
	return (1 + get_size(value / 10));
}

char		*ft_lltoa_unsigned(long long int value)
{
	char					*itoa;
	int						size;
	unsigned long long int	nb;

	nb = (unsigned long long int)value;
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
