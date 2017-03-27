/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:37:47 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 04:06:44 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** INIT & NEW FUNCTIONS
*/

t_coord	*ft_new_coord(int x, int y)
{
	t_coord	*new;

	new = malloc(sizeof(t_coord));
	new->x = x;
	new->y = y;
	return (new);
}

t_rect	*ft_new_rect(t_coord *coord1, t_coord *coord2, int color)
{
	t_rect	*new;

	new = malloc(sizeof(t_rect));
	new->coord1 = coord1;
	new->coord2 = coord2;
	new->color = color;
	return (new);
}

/*
int		**ft_init_map(t_coord *coord1)
{
	int		**map;
	int		i;
	int		j;
	t_coord	*coord2;

	coord2 = ft_new_coord(ft_get_i_map(coord1->x, 20, 5),
			ft_get_i_map(coord1->y, 20, 5));
	map = malloc(sizeof(int *) * ((coord2->y)));
	i = 0;
	while (i < (coord2->y))
	{
		j = 0;
		map[i] = malloc(sizeof(int) * ((coord2->x)));
		while (j < (coord2->x))
			map[i][j++] = 1;
		map[i][j] = 0;
		i++;
	}
	map[i] = malloc(sizeof(int));
	map[i][0] = 0;
	ft_free_coord(&coord2);
	return (map);
}
*/

t_mlx	*ft_new_mlx(int x, int y, char *title)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!(new->mlx = mlx_init()) ||
			!(new->win = mlx_new_window(new->mlx, x, y, title)))
		exit(0);
	new->x_size = x;
	new->y_size = y;
	new->bg_color = 0x00000000;
	new->grid = ft_new_rect(ft_new_coord(20, 20),
			ft_new_coord(x - 20, y - 20), 0x00FFFFFF);
	return (new);
}

t_data	*ft_new_data(t_info *info, t_mlx *mlx)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	new->info = info;
	new->mlx = mlx;
	return (new);
}
