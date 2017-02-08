/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 08:14:50 by apoisson          #+#    #+#             */
/*   Updated: 2017/01/19 08:28:57 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strspace(size_t size)
{
	char	*str;

	if (!(str = malloc(size + 1)))
		return (NULL);
	ft_bspace(str, size + 1);
	return (str);
}
