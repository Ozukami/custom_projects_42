/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:26:08 by qumaujea          #+#    #+#             */
/*   Updated: 2017/02/06 02:52:12 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(char value)
{
	if (value > -10 && value <= -1)
		return (2);
	if (value >= 0 && value < 10)
		return (1);
	if (value < -10)
		return (2 + get_size(-value / 10));
	return (1 + get_size(value / 10));
}

static int		neg_case(char *nb, char **itoa)
{
	if (*nb < 0)
	{
		*nb = -(*nb);
		itoa[0][0] = '-';
		return (1);
	}
	return (0);
}

char			*ft_sstoa(int value)
{
	char		*itoa;
	int			size;
	char		nb;
	int			neg;

	if (value == 128)
		return (ft_strdup("-128"));
	if (value == -128)
		return (ft_strdup("-128"));
	nb = value;
	size = get_size(nb);
	if (!(itoa = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size--] = '\0';
	neg = neg_case(&nb, &itoa);
	while (size >= neg)
	{
		itoa[size--] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (itoa);
}
