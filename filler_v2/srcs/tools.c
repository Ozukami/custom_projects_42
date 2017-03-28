/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:12:36 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 05:14:46 by apoisson         ###   ########.fr       */
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

void	ft_skip_n_line(int n)
{
	char	*line;

	while (n != 0)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
		n--;
	}
}

void	ft_set_coord(t_coord *coord, int x, int y)
{
	coord->x = x;
	coord->y = y;
}

void	ft_add_place(t_place **list, t_place *new)
{
	new->next = *list;
	*list = new;
}
