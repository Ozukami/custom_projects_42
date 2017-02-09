/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:43:21 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/19 12:54:56 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_size(int n)
{
	if (n < 0 && n > -10)
		return (2);
	if (n < 0)
		return (2 + ft_get_size(-n / 10));
	if (n < 10)
		return (1);
	return (1 + ft_get_size(n / 10));
}

char			*ft_itoa(int n)
{
	char	*rep;
	int		size;

	size = ft_get_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(rep = (char *)ft_memalloc(size + 1)))
		return (NULL);
	if (n == 0)
		rep[0] = '0';
	if (n < 0)
	{
		rep[0] = '-';
		n = -n;
	}
	rep[size--] = '\0';
	while (n > 0)
	{
		if (n < 10)
			rep[size--] = '0' + n;
		else
			rep[size--] = '0' + n % 10;
		n = n / 10;
	}
	return (rep);
}
