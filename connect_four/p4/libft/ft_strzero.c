/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 01:26:49 by qumaujea          #+#    #+#             */
/*   Updated: 2017/03/26 00:33:14 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strzero(size_t size)
{
	char	*str;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	ft_fill_zero(str, size + 1);
	return (str);
}
