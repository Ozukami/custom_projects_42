/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 03:42:21 by qumaujea          #+#    #+#             */
/*   Updated: 2017/03/29 03:53:20 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_coord		*ft_new_coord(int a, int b)
{
	t_coord		*new;

	new = ft_memalloc(sizeof(t_coord));
	ft_set_coord(new, a, b);
	return (new);
}
