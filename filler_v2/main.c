/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:11:26 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 04:35:08 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			ft_absolute(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void		ft_skip_n_line(int n)
{
	char	*line;

	while (n != 0)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
		n--;
	}
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

void		ft_get_piece_size(t_info *info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			PIECE_X = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			PIECE_Y = ft_atoi(line + i);
			break ;
		}
		i++;
	}
	if (info->t > 1)
		free_map(PIECE);
	free(PIECE);
	PIECE = ft_memalloc((sizeof(char *)) * (PIECE_X + 1));
	PIECE[PIECE_X] = 0;
}

void		ft_get_piece(t_info *info)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (i < PIECE_X)
	{
		get_next_line(0, &line);
		PIECE[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
}

int			ft_check_place(t_info *info, int x, int y, int verif)
{
	int		i;
	int		j;

	i = -1;
	if (x + info->x_piece > MAP_X || y + info->y_piece > MAP_Y)
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

void		ft_find_place(t_info *info, t_place **list)
{
	int		x;
	int		y;

	x = 0;
	while (MAP[x])
	{
		y = 0;
		while (MAP[x][y])
		{
			if (ft_check_place(info, x, y, 0))
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

void		free_list(t_place *list)
{
	if (list->next)
		free_list(list->next);
	free(list);
	list = NULL;
}

void		ft_send_coord(t_data *data, t_coord *coord, t_place **list)
{
	if (coord->x > -1 && coord->y > -1)
	{
		dprintf(1, "%d %d\n", coord->x, coord->y);
		ft_display_new_piece(data);
		free_list(*list);
		if (!SPEED)
			sleep(1);
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
	ft_find_place(info, &list);
	coord = ft_new_coord(-1, -1);
	current = list;
	while (current)
	{
		if (info->x_side > -1 || info->y_side > -1)
			if (ft_absolute(info->x_side - current->x) +
					ft_absolute(info->y_side - current->y) <
					ft_absolute(info->x_side - C_X) +
					ft_absolute(info->y_side - C_Y))
				ft_set_coord(coord, current->x, current->y);
		current = current->next;
	}
	if (list && coord->x == -1 && coord->y == -1)
		ft_set_coord(coord, list->x, list->y);
	ft_send_coord(data, coord, &list);
	return (coord);
}

void		ft_map_size(t_info *info)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			MAP_X = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			MAP_Y = ft_atoi(line + i);
			return ;
		}
		i++;
	}
	ft_strdel(&line);
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

void		ft_get_map(t_info *info, int t)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < MAP_X)
	{
		get_next_line(0, &line);
		if (!t)
			MAP_PREV[i] = ft_strsub(line, 4, MAP_Y);
		else
			ft_strdel(&(MAP[i]));
		MAP[i] = ft_strsub(line, 4, MAP_Y);
		ft_strdel(&line);
		i++;
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

int			ft_update_map(t_data *data)
{
	char	*line;

	line = NULL;
	if ((INFO->t)++)
	{
		ft_skip_n_line(2);
		ft_get_map(INFO, INFO->t);
		ft_wild_ennemy_appears(data);
	}
	get_next_line(0, &line);
	ft_get_piece_size(INFO, line);
	ft_strdel(&line);
	ft_get_piece(INFO);
	return (1);
}

int			ft_process(t_data *data)
{
	t_coord	*coord;
	int		x;
	int		y;

	ft_update_map(data);
	coord = ft_get_place(data, (data)->info);
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
	free(coord);
	mlx_do_sync(D_MLX);
	return (1);
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

int			main(void)
{
	t_info	*info;
	t_mlx	*mlx;
	t_data	*data;

	info = ft_new_info();
	ft_map_size(info);
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
