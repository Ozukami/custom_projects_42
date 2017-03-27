/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:37:37 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 03:42:08 by apoisson         ###   ########.fr       */
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
			if ((data->info->map_prev)[x][y] == '*')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(y, 20, 5) + 1,
							ft_get_i_grid(x, 20, 5) + 1),
						ft_new_coord(3, 4), 0x00ECE142));
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
	while (++y < ((data)->info)->x_map)
	{
		x = -1;
		while (++x < ((data)->info)->y_map)
		{
			if ((((data)->info)->map)[y][x] == 'O'
					|| (((data)->info)->map)[y][x] == 'o')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(x, 20, 5) + 1, I_GRID(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x00FF0000));
			else if ((((data)->info)->map)[y][x] == 'x'
					|| (((data)->info)->map)[y][x] == 'X')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(x, 20, 5) + 1, I_GRID(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x000000FF));
			else
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(x, 20, 5) + 1, I_GRID(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x0000FF00));
		}
	}
}

int			ft_update_map(t_data *data)
{
	char	*line;

	line = NULL;
	if ((((data)->info)->t)++)
	{
		ft_skip_n_line(2);
		ft_get_map(&((data)->info), ((data)->info)->t);
		ft_wild_ennemy_appears(&((data)->info), data);
	}
	get_next_line(0, &line);
	ft_get_piece_size(&((data)->info), line);
	ft_strdel(&line);
	ft_get_piece(&((data)->info));
	return (1);
}
