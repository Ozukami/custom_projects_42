/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:35:22 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 02:35:37 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** GET FUNCTIONS
*/

/*
** i = x ou y
** i_border = x_border ou y_border
** size = size d'1 cellule
*/

int		ft_get_i_map(int i, int i_border, int size)
{
	return (((i - (i_border)) / size));
}

/*
** i = x ou y
** i_border = x_border ou y_border
** size = size d'1 cellule
*/

int		ft_get_i_grid(int i, int i_border, int size)
{
	return ((i * size) + i_border);
}
