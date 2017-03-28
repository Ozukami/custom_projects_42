/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 23:15:06 by qumaujea          #+#    #+#             */
/*   Updated: 2017/03/28 23:16:26 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_send_coord(t_data *data, t_coord *coord)
{
	if (coord->x > -1 && coord->y > -1)
	{
		ft_display_coord(coord->x, coord->y);
		ft_display_new_piece(data);
		if (!SPEED)
			sleep(1);
	}
	else
		ft_display_coord(0, 0);
}

void		ft_wild_ennemy_appears(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (D_MAP[++x])
	{
		y = -1;
		while (D_MAP[x][++y])
		{
			if (D_MAP[x][y] != D_MAP_PREV[x][y])
			{
				if (D_MAP[x][y] != INFO->player
						&& D_MAP[x][y] != INFO->player - 32)
				{
					ft_fill_rectangle(data, ft_new_rect(ft_new_coord(I_GRID(
							y, BORDER, CELL_SIZE) + 1, I_GRID(x, BORDER,
							CELL_SIZE) + 1), ft_new_coord(CELL_SIZE - 2,
							CELL_SIZE - 1), 0x000000FF));
					INFO->x_side = x;
					INFO->y_side = y;
				}
				D_MAP_PREV[x][y] = D_MAP[x][y];
			}
		}
	}
}

int			ft_process(t_data *data)
{
	t_coord	*coord;
	int		x;
	int		y;

	ft_update_map(data);
	coord = ft_get_place(INFO);
	if (!(C_X == -1 && C_Y == -1))
	{
		x = -1;
		while (D_PIECE[++x])
		{
			y = -1;
			while (D_PIECE[x][++y])
				if (D_PIECE[x][y] == '*')
					ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								I_GRID(C_Y + y, BORDER, CELL_SIZE) + 1,
								I_GRID(C_X + x, BORDER, CELL_SIZE) + 1),
							ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
							0x00FF0000));
		}
	}
	ft_send_coord(data, coord);
	free(coord);
	mlx_do_sync(D_MLX);
	return (1);
}

int			main(void)
{
	t_info	*info;
	t_mlx	*mlx;
	t_data	*data;

	info = ft_new_info();
	ft_get_map_size(info);
	info->map = ft_memalloc((sizeof(char *)) * (MAP_X + 1));
	info->map_prev = ft_memalloc((sizeof(char *)) * (MAP_X + 1));
	(info->map)[MAP_X] = 0;
	(info->map_prev)[MAP_X] = 0;
	ft_skip_n_line(1);
	ft_get_map(info, 0);
	mlx = ft_new_mlx((MAP_Y * CELL_SIZE) + BORDER * 2,
			(MAP_X * CELL_SIZE) + BORDER * 2, "Filler");
	data = ft_new_data(info, mlx);
	ft_display_grid(data);
	ft_display_map(data);
	mlx_do_sync(((data)->mlx)->mlx);
	mlx_hook(mlx->win, 2, 0, &ft_key_handler, data);
	mlx_hook(mlx->win, 17, 0, &ft_exit, data);
	mlx_loop_hook(mlx->mlx, &ft_process, data);
	mlx_loop(mlx->mlx);
	return (0);
}
