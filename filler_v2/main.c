/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 23:52:54 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 02:21:35 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <stdio.h>

int			ft_absolute(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

t_place		*ft_new_place(int x, int y)
{
	t_place	*new;

	new = ft_memalloc(sizeof(t_place));
	new->x = x;
	new->y = y;
	return (new);
}

void		ft_set_coord(t_coord *coord, int x, int y)
{
	coord->x = x;
	coord->y = y;
}

void		ft_add_place(t_place **list, t_place *new)
{
	new->next = *list;
	*list = new;
}

void		ft_get_piece_size(t_info **info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			(*info)->x_piece = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			(*info)->y_piece = ft_atoi(line + i);
			break ;
		}
		i++;
	}
	(*info)->piece = ft_memalloc((sizeof(char *)) * ((*info)->x_piece + 1));
	((*info)->piece)[(*info)->x_piece] = 0;
}

void		ft_get_piece(t_info **info)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (i < (*info)->x_piece)
	{
		get_next_line(0, &line);
		((*info)->piece)[i] = ft_strdup(line);
		i++;
	}
}

int			ft_check_place(t_info *info, int x, int y, int verif)
{
	int		i;
	int		j;

	i = -1;
	if (x + info->x_piece > info->x_map || y + info->y_piece > info->y_map)
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

void		ft_find_place(t_info **info, t_place **list)
{
	int		x;
	int		y;

	x = 0;
	while (((*info)->map)[x])
	{
		y = 0;
		while (((*info)->map)[x][y])
		{
			if (ft_check_place(*info, x, y, 0))
				ft_add_place(list, ft_new_place(x, y));
			y++;
		}
		x++;
	}
}

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

void		ft_send_coord(t_data *data, t_coord *coord)
{
	if (coord->x > -1 && coord->y > -1)
	{
		dprintf(1, "%d %d\n", coord->x, coord->y);
		ft_display_new_piece(data);
	}
	else
		dprintf(1, "%d %d\n", 0, 0);
}

t_coord		*ft_get_place(t_data *data, t_info *info)
{
	t_coord	*coord;
	t_place	*list;
	t_place	*current;

	list = NULL;
	ft_find_place(&info, &list);
	coord = ft_new_coord(-1, -1);
	current = list;
	while (current)
	{
		if (info->x_side > -1 || info->y_side > -1)
			if (ft_absolute(info->x_side - current->x) +
					ft_absolute(info->y_side - current->y) <
					ft_absolute(info->x_side - coord->x) +
					ft_absolute(info->y_side - coord->y))
				ft_set_coord(coord, current->x, current->y);
		current = current->next;
	}
	if (list && coord->x == -1 && coord->y == -1)
		ft_set_coord(coord, list->x, list->y);
	ft_send_coord(data, coord);
	return (coord);
}

void		ft_map_size(t_info **info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			(*info)->x_map = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			(*info)->y_map = ft_atoi(line + i);
			return ;
		}
		i++;
	}
}

void		ft_wild_ennemy_appears(t_info **info, t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (((*info)->map)[++x])
	{
		y = -1;
		while (((*info)->map)[x][++y])
		{
			if (((*info)->map)[x][y] != ((*info)->map_prev)[x][y])
			{
				if (((*info)->map)[x][y] != (*info)->player
						&& ((*info)->map)[x][y] != (*info)->player - 32)
				{
					ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								ft_get_i_grid(y, 20, 5) + 1,
								ft_get_i_grid(x, 20, 5) + 1),
							ft_new_coord(3, 4), 0x000000FF));
					(*info)->x_side = x;
					(*info)->y_side = y;
				}
				((*info)->map_prev)[x][y] = ((*info)->map)[x][y];
			}
		}
	}
}

void		ft_get_map(t_info **info, int t)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < (*info)->x_map)
	{
		get_next_line(0, &line);
		if (!t)
			((*info)->map_prev)[i] = ft_strdup(ft_strsub(line, 4,
					(*info)->y_map));
		else
			free(((*info)->map)[i]);
		((*info)->map)[i] = ft_strdup(ft_strsub(line, 4, (*info)->y_map));
		i++;
	}
}

void		ft_display_map(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < ((data)->info)->x_map)
	{
		x = 0;
		while (x < ((data)->info)->y_map)
		{
			if ((((data)->info)->map)[y][x] == 'O'
					|| (((data)->info)->map)[y][x] == 'o')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(x, 20, 5) + 1,
							ft_get_i_grid(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x00FF0000));
			else if ((((data)->info)->map)[y][x] == 'x'
					|| (((data)->info)->map)[y][x] == 'X')
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(x, 20, 5) + 1,
							ft_get_i_grid(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x000000FF));
			else
				ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(x, 20, 5) + 1,
							ft_get_i_grid(y, 20, 5) + 1),
						ft_new_coord(3, 4), 0x0000FF00));
			x++;
		}
		y++;
	}
	mlx_do_sync(((data)->mlx)->mlx);
}

int			ft_update_map(t_data *data)
{
	char	*line;

	line = NULL;
	if ((((data)->info)->t)++)
	{
		get_next_line(0, &line);
		get_next_line(0, &line);
		ft_get_map(&((data)->info), ((data)->info)->t);
		ft_wild_ennemy_appears(&((data)->info), data);
	}
	get_next_line(0, &line);
	ft_get_piece_size(&((data)->info), line);
	ft_get_piece(&((data)->info));
	return (1);
}

int			ft_process(t_data *data)
{
	t_coord	*coord;
	int		x;
	int		y;

	ft_update_map(data);
	coord = ft_get_place(data, (data)->info);
	if (!(coord->x == -1 && coord->y == -1))
	{
		x = -1;
		while ((((data)->info)->piece)[++x])
		{
			y = -1;
			while ((((data)->info)->piece)[x][++y])
			{
				if ((((data)->info)->piece)[x][y] == '*')
					ft_fill_rectangle(data, ft_new_rect(ft_new_coord(
								ft_get_i_grid(coord->y + y, 20, 5) + 1,
								ft_get_i_grid(coord->x + x, 20, 5) + 1),
							ft_new_coord(3, 4), 0x00FF0000));
			}
		}
	}
	mlx_do_sync(((data)->mlx)->mlx);
	return (1);
}

int			ft_exit(void)
{
	exit(0);
	return (1);
}

int			ft_key_handler(int key)
{
	if (key == 53)
		ft_exit();
	return (0);
}

int			main(void)
{
	t_info	*info;
	char	*line;
	t_mlx	*mlx;
	t_data	*data;

	get_next_line(0, &line);
	info = ft_new_info(((line[10] == '1') ? 'o' : 'x'));
	get_next_line(0, &line);
	ft_map_size(&info, line);
	info->map = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	info->map_prev = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	(info->map)[info->x_map] = 0;
	(info->map_prev)[info->x_map] = 0;
	get_next_line(0, &line);
	ft_get_map(&info, 0);
	mlx = ft_new_mlx((info->y_map * 5) + 40, (info->x_map * 5) + 40, "Filler");
	data = ft_new_data(info, mlx);
	ft_display_grid(data);
	ft_display_map(data);
	mlx_hook(mlx->win, 2, 0, &ft_key_handler, 0);
	mlx_hook(mlx->win, 17, 0, &ft_exit, data);
	mlx_loop_hook(mlx->mlx, &ft_process, data);
	mlx_loop(mlx->mlx);
	return (0);
}
