/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:05:17 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 05:05:20 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_display_new_piece(t_data *data)
{
	int			x;
	int			y;

	x = 0;
	while ((data->info->piece)[x])
	{
		y = 0;
		while ((data->info->piece)[x][y])
		{
			if ((INFO->map_prev)[x][y] == '*')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(y, BORDER, CELL_SIZE) + 1,
							ft_get_i_grid(x, BORDER, CELL_SIZE) + 1),
						ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
						0x00ECE142));
			y++;
		}
		x++;
	}
}

void		ft_display_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < INFO->x_map)
	{
		x = -1;
		while (++x < INFO->y_map)
		{
			if ((INFO->map)[y][x] != '.')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(x, BORDER, CELL_SIZE) + 1,
								I_GRID(y, BORDER, CELL_SIZE) + 1),
						ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
						0x000000FF));
			else
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(x, BORDER, CELL_SIZE) + 1,
								I_GRID(y, BORDER, CELL_SIZE) + 1),
						ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
						0x0000FF00));
		}
	}
}

int			ft_exit(t_data *data)
{
	free_data(data);
	exit(0);
	return (1);
}

int			ft_key_handler(int key, t_data *data)
{
	if (key == 53)
		ft_exit(data);
	if (key == 49)
		SPEED = (SPEED) ? 0 : 1;
	return (0);
}
