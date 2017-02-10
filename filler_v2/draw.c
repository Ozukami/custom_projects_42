/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:40:17 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 10:16:40 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** DRAW FUNCTIONS
*/

/*
** Draw Line (with direction)
*/

void	ft_draw_line(t_mlx *mlx, int x, int y,
		int value, int dir, int color)
{
	int	i;

	i = 0;
	while (i < value)
	{
		x += ((dir == 1) ? 1 : 0);
		x += ((dir == 3) ? -1 : 0);
		y += ((dir == 0) ? 1 : 0);
		y += ((dir == 2) ? -1 : 0);
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
		i++;
	}
}

/*
** Fill Rectangle
*/

void	ft_fill_rectangle(t_mlx *mlx, int x, int y, int col, int line, int color)
{
	int		i;

	i = 0;
	while (i < line)
	{
		ft_draw_line(mlx->mlx, x, y + i, col, 1, color);
		i++;
	}	
}

/*
** Fill Square
*/

void	ft_fill_square(t_mlx *mlx, int x, int y, int size, int color)
{
	ft_fill_rectangle(mlx->mlx, x, y, size, size, color);
}

/*
** Draw Rectangle
*/

void	ft_draw_rectangle(t_mlx *mlx, int x, int y, int col, int line, int color)
{
	ft_draw_line(mlx->mlx, x, y, col, 1, color);
	ft_draw_line(mlx->mlx, x, y, line, 0, color);
	ft_draw_line(mlx->mlx, x, y + line, col, 1, color);
	ft_draw_line(mlx->mlx, x + col, y, line, 0, color);
}

/*
** Draw Square
*/

void	ft_draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
	ft_draw_rectangle(mlx, x, y, size, size, color);
}

/*
** DISPLAY FUNCTIONS
*/

void	ft_display_grid(t_mlx *mlx)
{
	int			x;
	int			y;
	int			x_border;
	int			y_border;

	y = 0;
	x_border = 20;
	y_border = 20;
	while (y < (((mlx->y_size - (y_border + x_border)) / 5)))
	{
		x = 0;
		while (x < (((mlx->x_size - 2 * x_border)) / 5))
		{
			ft_draw_square(mlx, (x * 5) + x_border,
					(y * 5) + y_border, 5, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}
