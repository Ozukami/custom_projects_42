/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 04:28:04 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/29 04:30:49 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rect	*ft_new_rect(t_coord *coord1, t_coord *coord2, int color)
{
	t_rect	*new;

	if (!(new = ft_memalloc(sizeof(t_rect))))
		return (NULL);
	new->coord1 = coord1;
	new->coord2 = coord2;
	new->color = color;
	return (new);
}
