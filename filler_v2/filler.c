/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:41:35 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/13 03:37:47 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** DRAW FUN
*/

void			ft_draw_line(t_data *data, t_coord *pos_ini, t_coord *charac,
		int color)
{
	int			i;

	i = 0;
	while (i < charac->x)
	{
		pos_ini->x += ((charac->y == RIGHT) ? 1 : 0);
		pos_ini->x += ((charac->y == LEFT) ? -1 : 0);
		pos_ini->y += ((charac->y == DOWN) ? 1 : 0);
		pos_ini->y += ((charac->y == UP) ? -1 : 0);
		mlx_pixel_put(MLX, WIN, pos_ini->x, pos_ini->y, color);
		i++;
	}
}

void			ft_draw_rectangle(t_data *data, t_rect *rect)
{
	ft_draw_line(data, rect->coord1,
			ft_new_coord(R_X2, RIGHT), R_COLOR);
	ft_draw_line(data, rect->coord1,
			ft_new_coord(R_Y2, DOWN), R_COLOR);
	ft_draw_line(data, ft_new_coord(R_X1, R_Y2),
			ft_new_coord(R_X2, RIGHT), R_COLOR);
	ft_draw_line(data, ft_new_coord(R_X2, R_Y1),
			ft_new_coord(R_Y2, DOWN), R_COLOR);
}

/*
** MAIN PROCESS FUN
*/

int				ft_exit(void)
{
	exit(0);
	return (0);
}

int				ft_process(t_data *data)
{
	(void)data;
	return (1);
}

/*
** DISPLAY FUN
*/

void			ft_display_grid(t_data *data)
{
	int			x;
	int			y;

	printf("{%d,%d}\n", ((WIN_X - (BORDER * 2)) / CELL_SIZE), 
			((WIN_Y - (BORDER * 2)) / CELL_SIZE));
	y = 0;
	while (y < (((WIN_Y - (BORDER * 2)) / CELL_SIZE)) + 1)
	{
		ft_draw_line(data,
				ft_new_coord(BORDER, (y * CELL_SIZE) + BORDER),
				ft_new_coord(WIN_Y - (BORDER *2), RIGHT),
				0x00FFFFFF);
		y++;
	}
	x = 0;
	while (x < (((WIN_X - 2 * BORDER)) / CELL_SIZE) + 1)
	{
		ft_draw_line(data,
				ft_new_coord((x * CELL_SIZE) + BORDER, BORDER),
				ft_new_coord(WIN_X - (BORDER *2), DOWN),
				0x00FFFFFF);
		x++;
	}
}

/*
** GET FUN
*/

void			ft_get_map(t_info *info, int t)
{
	int			i;
	char		*line;

	i = 0;
	line = NULL;
	while (i < (info->map)->x)
	{
		get_next_line(0, &line);
		printf("%d > %s\n", i + 4, line);
		if (!t)
			I_MAP_PREV[i] = ft_strsub(line, 4, (info->map)->y);
		else
			ft_strdel(&(I_MAP[i]));
		I_MAP[i] = ft_strsub(line, 4, (info->map)->y);
		free(line);
		i++;
	}
}

t_coord			*ft_get_map_size(char *line)
{
	t_coord		*map_size;
	int			i;

	map_size = ft_new_coord(0, 0);
	i = 0;
	while (line[i] && (!(line[i] >= '0' && line[i] <= '9')))
		i++;
	map_size->x = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	map_size->y = ft_atoi(line + i);
	return (map_size);
}

/*
** NEW FUN
*/

t_map			*ft_new_map(char **map, t_coord *coord)
{
	t_map		*new;

	if (!(new = ft_memalloc(sizeof(t_map))))
		exit(0);
	new->map = map;
	new->x = coord->x;
	new->y = coord->y;
	return (new);
}

t_coord			*ft_new_coord(int x, int y)
{
	t_coord		*new;

	if (!(new = ft_memalloc(sizeof(t_coord))))
		exit(0);
	new->x = x;
	new->y = y;
	return (new);
}

t_rect			*ft_new_rect(t_coord *coord1, t_coord *coord2, int color)
{
	t_rect		*new;

	if (!(new = ft_memalloc(sizeof(t_rect))))
		exit(0);
	new->coord1 = coord1;
	new->coord2 = coord2;
	new->color = color;
	return (new);
}

t_grid			*ft_new_grid(int x, int y, int border, int cell_size)
{
	t_grid		*new;

	if (!(new = ft_memalloc(sizeof(t_grid))))
		exit(0);
	printf("[%d,%d] -> [%d,%d]\n", border, border, x - border, y - border);
	new->rect = ft_new_rect(ft_new_coord(border, border),
			ft_new_coord(x - border, y - border), 0x00FFFFFF);
	new->size = cell_size;
	new->x = (x - border) / cell_size;
	new->y = (y - border) / cell_size;
	return (new);
}

/*
** INIT FUN
*/

void			ft_init_map(t_info *info)
{
	char		*line;
	t_coord		*coord;

	get_next_line(0, &line);
	coord = ft_get_map_size(line);
	info->map = ft_new_map(NULL, coord);
	info->map_prev = ft_new_map(NULL, coord);
	ft_strdel(&line);
	free(coord);
}

t_info			*ft_init_info(void)
{
	t_info		*new;
	char		*line;

	if (!(new = ft_memalloc(sizeof(t_info))))
		exit(0);
	printf("1\n");
	get_next_line(0, &line);
	printf("2 > %s\n", line);
	new->player = ((line[10] == '1') ? 'o' : 'x');
	new->ennemy = ((line[10] == '1') ? 'x' : 'o');
	ft_strdel(&line);
	ft_init_map(new);
	ft_strdel(&line);
	get_next_line(0, &line);
	printf("3 > %s\n", line);
	ft_strdel(&line);
	if ((!(new->map->map = ft_memalloc((new->map)->y + 1)))
			|| (!(new->map_prev->map = ft_memalloc((new->map)->y + 1))))
		exit(0);
//	ft_get_map(new, 0);
	new->piece = NULL;
	new->aim = NULL;
	new->t = 0;
	return (new);
}

t_mlx_env		*ft_init_mlx_env(t_info *info,
		int cell_size, int border)
{
	t_mlx_env	*new;

	if ((!(new = ft_memalloc(sizeof(t_mlx_env)))
				|| (!(new->mlx = mlx_init()))))
		exit(0);
	new->x = (info->map->x * cell_size) + border;
	new->y = (info->map->y * cell_size) + border;
	printf("[%d,%d]\n", new->x, new->y);
	new->win = mlx_new_window(new->mlx, new->x, new->y, "Filler");
	new->grid = ft_new_grid(new->x, new->y, border / 2, cell_size);
	new->border = border / 2;
	return (new);
}

t_list			*ft_init_list()
{
	t_list		*new;

	if (!(new = ft_memalloc(sizeof(t_list))))
		exit(0);
	return (new);
}

t_data			*ft_init_data()
{
	t_data		*new;

	if (!(new = ft_memalloc(sizeof(t_data))))
		exit(0);
	new->info = ft_init_info();
	new->mlx_env = ft_init_mlx_env(new->info, 5, 40);
	new->list = NULL;
	return (new);
}

/*
** MAIN
*/

int				main(void)
{
	t_data		*data;

	data = ft_init_data();
	ft_display_grid(data);
//	ft_display_map(data);
	mlx_hook(WIN, 17, 0, &ft_exit, &data);
	mlx_loop_hook(MLX, &ft_process, &data);
	mlx_loop(MLX);
	return (0);
}
