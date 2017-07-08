/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 06:06:29 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/11 09:30:26 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sub(const char *str, int *neg)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*neg = 1;
		i++;
	}
	return (i);
}

int			ft_atoi_base(const char *str, int base)
{
	int	rep;
	int	neg;
	int	i;

	rep = 0;
	neg = 0;
	i = ft_sub(str, &neg);
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')
				|| (str[i] >= 'A' && str[i] <= 'F')
				|| (str[i] >= 'a' && str[i] <= 'f')))
	{
		if (str[i] && (str[i] >= '0' && str[i] <= '9'))
			rep = (rep * base) + str[i] - '0';
		else if ((str[i] >= 'A' && str[i] <= 'A' + base - 10)
				&& base > 10 && !neg)
			rep = (rep * base) + str[i] - 'A' + 10;
		else if ((str[i] >= 'a' && str[i] <= 'a' + base - 10)
				&& base > 10 && !neg)
			rep = (rep * base) + str[i] - 'a' + 10;
		else
			break ;
		i++;
	}
	return (((neg) ? -rep : rep));
}
