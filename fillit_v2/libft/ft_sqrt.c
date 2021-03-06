/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 12:14:54 by qumaujea          #+#    #+#             */
/*   Updated: 2016/11/27 12:36:00 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sqrt(size_t n)
{
	size_t	sqrt;

	sqrt = 0;
	while (sqrt * sqrt <= n)
	{
		if (sqrt * sqrt == n)
			return (sqrt);
		sqrt++;
	}
	return (0);
}
