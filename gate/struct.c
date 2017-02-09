/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:37:47 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 00:08:09 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

/*
** INIT FUNCTIONS
*/

t_rect	*ft_new_rect(int x1, int y1, int x2, int y2)
{
	t_rect	*new;

	new = malloc(sizeof(t_rect));
	new->x1 = x1;
	new->y1 = y1;
	new->x2 = x2;
	new->y2 = y2;
	return (new);
}

int		**ft_init_map(int x, int y)
{
	int		**map;
	int		i;
	int		j;
	int		x_max;
	int		y_max;

	x_max = ft_get_i_map(x, 20, 25);
	y_max = ft_get_i_map(y, 100, 25);
	map = malloc(sizeof(int *) * (y_max));
	i = 0;
	j = 0;
	while (i < y_max)
	{
		j = 0;
		map[i] = malloc(sizeof(int) * (x_max));
		while (j < x_max)
		{
			map[i][j] = 1;
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	map[i] = malloc(sizeof(int));
	map[i][0] = 0;
	return (map);
}

t_mlx	*ft_new_mlx(int x, int y, char *title)
{
	t_mlx	*new;

	new	= malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, x, y, title);
	new->x = x;
	new->y = y;
	new->pos_x = x / 2;
	new->pos_y = y / 2;
	new->draw = 1;
	new->color = 0x00000000;
	new->gates = NULL;
	new->player = NULL;
	new->grid = ft_new_rect(20, 100, x - 20, y - 20);
	new->map = ft_init_map(x, y);
	return (new);
}

t_gate	*ft_new_gate(int x, int y, int col, int line, int color, char *title)
{
	t_gate	*new;

	new = malloc(sizeof(t_gate));
	new->title = title;
	new->x = x;
	new->y = y;
	new->col = col;
	new->line = line;
	new->color = color;
	new->next = NULL;
	return (new);
}

t_player	*ft_new_player(int x, int y, int size, char *name, int color)
{
	t_player	*new;

	new = malloc(sizeof(t_player));
	new->name = name;
	new->color = color;
	new->x = x;
	new->y = y;
	new->size = size;
	new->life = 3;
	return (new);
}

/*
** MOD FUNCTIONS
*/

void	ft_add_gate(t_mlx **mlx, t_gate *new_gate)
{
	new_gate->next = (*mlx)->gates;
	(*mlx)->gates = new_gate;
}

/*
 * GET FUNCTIONS
 */

int		ft_get_i_map(int i, int i_border, int size)
{
	return (((i - (i_border)) / size));
}
