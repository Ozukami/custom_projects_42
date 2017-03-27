/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:40:17 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 02:22:46 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** DRAW FUNCTIONS
*/

/*
** Draw Line (with direction)
*/

void	ft_draw_line(t_data *data, t_coord *pos_ini,
		t_coord *charac, int color)
{
	int	i;

	i = 0;
	while (i < charac->x + 1)
	{
		mlx_pixel_put(D_MLX, D_WIN, pos_ini->x, pos_ini->y, color);
		pos_ini->x += ((DIRECTION == RIGHT) ? 1 : 0);
		pos_ini->x += ((DIRECTION == LEFT) ? -1 : 0);
		pos_ini->y += ((DIRECTION == DOWN) ? 1 : 0);
		pos_ini->y += ((DIRECTION == UP) ? -1 : 0);
		i++;
	}
}

/*
** Fill Rectangle
*/

void	ft_fill_rectangle(t_data *data, t_rect *rect)
{
	int		i;

	i = -1;
	while (++i < rect->coord2->y)
		ft_draw_line(data, ft_new_coord(R_X1, R_Y1 + i),
				ft_new_coord(R_X2, 1), R_COLOR);
}

/*
** Draw Rectangle
*/

void	ft_draw_rectangle(t_data *data, t_rect *rect)
{
	ft_draw_line(data, R_1, ft_new_coord(R_X2, RIGHT), R_COLOR);
	ft_draw_line(data, R_1, ft_new_coord(R_Y2, DOWN), R_COLOR);
	ft_draw_line(data, ft_new_coord(R_X1, R_Y1 + R_Y2),
			ft_new_coord(R_X2, RIGHT), R_COLOR);
	ft_draw_line(data, ft_new_coord(R_X1 + R_X2, R_Y2),
			ft_new_coord(R_Y2, DOWN), R_COLOR);
}

/*
** DISPLAY FUNCTIONS
*/

void	ft_display_grid(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (((D_MLX_Y - 2 * 20)) / 5) + 1)
	{
		ft_draw_line(data,
				ft_new_coord(20, (y * 5) + 20),
				ft_new_coord(D_MLX_X - (2 * 20), RIGHT),
				0x00FFFFFF);
		y++;
	}
	x = 0;
	while (x < (((D_MLX_X - 2 * 20)) / 5) + 1)
	{
		ft_draw_line(data,
				ft_new_coord((x * 5) + 20, 20),
				ft_new_coord(D_MLX_Y - (2 * 20), DOWN),
				0x00FFFFFF);
		x++;
	}
}
