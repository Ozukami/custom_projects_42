/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:22:03 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 23:21:44 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			ft_check_place(t_info *info, int x, int y, int verif)
{
	int		i;
	int		j;

	i = -1;
	if (x + info->x_piece > MAP_X || y + info->y_piece > MAP_Y)
		return (0);
	while ((info->piece)[++i])
	{
		j = -1;
		while ((info->piece)[i][++j])
		{
			if ((info->piece)[i][j] != '.'
					&& (info->map)[i + x][j + y] != '.')
			{
				if ((info->map)[i + x][j + y] != info->player
						&& (info->map)[i + x][j + y] != info->player - 32)
					return (0);
				else if (verif++)
					return (0);
			}
		}
	}
	if (verif)
		return (1);
	return (0);
}

void		ft_find_place(t_info *info, t_place **list)
{
	int		x;
	int		y;

	x = 0;
	while (MAP[x])
	{
		y = 0;
		while (MAP[x][y])
		{
			if (ft_check_place(info, x, y, 0))
				ft_add_place(list, ft_new_place(x, y));
			y++;
		}
		x++;
	}
}

t_coord		*ft_get_place(t_info *info)
{
	t_coord	*coord;
	t_place	*list;
	t_place	*current;

	list = NULL;
	ft_find_place(info, &list);
	coord = ft_new_coord(-1, -1);
	current = list;
	while (current)
	{
		if (info->x_side > -1 || info->y_side > -1)
			if (ft_absolute(info->x_side - current->x) +
					ft_absolute(info->y_side - current->y) <
					ft_absolute(info->x_side - C_X) +
					ft_absolute(info->y_side - C_Y))
				ft_set_coord(coord, current->x, current->y);
		current = current->next;
	}
	if (list && coord->x == -1 && coord->y == -1)
	{
		ft_set_coord(coord, list->x, list->y);
		free_list(&list);
	}
	return (coord);
}

void		ft_display_coord(int x, int y)
{
	ft_putnbr_fd(x, 1);
	ft_putchar(' ');
	ft_putnbr_fd(y, 1);
	ft_putchar('\n');
}
