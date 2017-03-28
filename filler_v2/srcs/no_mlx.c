/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:51:49 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 23:16:09 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

	ft_update_map(data);
	coord = ft_get_place(data->info);
	if (coord->x > -1 && coord->y > -1)
		ft_display_coord(coord->x, coord->y);
	else
		ft_display_coord(0, 0);
	free(coord);
	return (1);
}

int			main(void)
{
	t_info	*info;
	t_data	*data;

	info = ft_new_info();
	ft_get_map_size(info);
	info->map = ft_memalloc((sizeof(char *)) * (MAP_X + 1));
	info->map_prev = ft_memalloc((sizeof(char *)) * (MAP_X + 1));
	(info->map)[MAP_X] = 0;
	(info->map_prev)[MAP_X] = 0;
	ft_skip_n_line(1);
	ft_get_map(info, 0);
	data = ft_new_data(info, NULL);
	while (1)
		ft_process(data);
	return (0);
}
