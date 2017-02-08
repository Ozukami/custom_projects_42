/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:40:17 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 10:44:35 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

/*
** Draw Line
*/

void	ft_put_line(void *mlx, void *win, int x, int y,
		int value, int dir, int color)
{
	int	i;

	i = 0;
	while (i < value)
	{
		if (!dir)
			y++;
		if (dir == 1)
			x++;
		if (dir == 2)
			y--;
		if (dir == 3)
			x--;
		mlx_pixel_put(mlx, win, x, y, color);
		i++;
	}
}

/*
** Draw Rectangle
*/

void	ft_fill_rectangle(void *mlx, void *win, int x, int y,
		int col, int line, int color)
{
	int		i;

	i = 0;
	while (i < line)
	{
		ft_put_line(mlx, win, x, y + i, col, 1, color);
		i++;
	}	
}
