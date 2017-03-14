/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:41:35 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/14 06:10:11 by apoisson         ###   ########.fr       */
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
	while (i < charac->x + 1)
	{
		mlx_pixel_put(MLX, WIN, pos_ini->x, pos_ini->y, color);
		pos_ini->x += ((charac->y == RIGHT) ? 1 : 0);
		pos_ini->x += ((charac->y == LEFT) ? -1 : 0);
		pos_ini->y += ((charac->y == DOWN) ? 1 : 0);
		pos_ini->y += ((charac->y == UP) ? -1 : 0);
		i++;
	}
}

void			ft_fill_rect(t_data *data, t_rect *rect)
{
	int			i;

	i = -1;
	while (++i < rect->coord2->y)
		ft_draw_line(data,
				ft_new_coord(rect->coord1->x, rect->coord1->y + i),
				ft_new_coord(rect->coord2->x, 1),
				rect->color);
}

void			ft_draw_rect(t_data *data, t_rect *rect)
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

void			ft_display_map(t_data *data)
{
	int			x;
	int			y;
	int			color;

	printf("START ft_display_map\n");
	y = -1;
	while (++y < ((MAP_CURR)->y))
	{
		x = -1;
		while (++x < (MAP_CURR)->x)
		{
			if (MAP[y][x] == 'O' || MAP[y][x] == 'o')
				color = 0x00FF0000;
			else if (MAP[y][x] == 'X' || MAP[y][x] == 'x')
				color = 0x000000FF;
			else
				color = 0x0000FF00;
			ft_fill_rect(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(x, data), ft_get_i_grid(y, data)),
						ft_new_coord(CELL_SIZE - 1, CELL_SIZE - 1), color));
		}
		printf("	%d\n", y);
	}
	printf("END ft_display_map\n");
}

void			ft_display_grid(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (y < (((WIN_Y - 2 * BORDER)) / CELL_SIZE) + 1)
	{
		ft_draw_line(data,
				ft_new_coord(BORDER, (y * CELL_SIZE) + BORDER),
				ft_new_coord(WIN_X - (BORDER *2), RIGHT),
				0x00FFFFFF);
		y++;
	}
	x = 0;
	while (x < (((WIN_X - 2 * BORDER)) / CELL_SIZE) + 1)
	{
		ft_draw_line(data,
				ft_new_coord((x * CELL_SIZE) + BORDER, BORDER),
				ft_new_coord(WIN_Y - (BORDER *2), DOWN),
				0x00FFFFFF);
		x++;
	}
}

/*
** GET FUN
*/

int				ft_get_i_grid(int i, t_data *data)
{
	return ((i * CELL_SIZE) + BORDER);
}

int				ft_get_i_map(int i, t_data *data)
{
	return ((i - BORDER) / CELL_SIZE);
}

void			ft_get_map(t_data *data)
{
	int			i;
	char		*line;

	i = 0;
	line = NULL;
	while (i < (MAP_CURR)->y)
	{
		get_next_line(0, &line);
		if (!(TURN++))
			(MAP_PREV->map)[i] = ft_strsub(line, 4, MAP_CURR->x);
		else
			ft_strdel(&(MAP[i]));
		MAP[i] = ft_strsub(line, 4, MAP_CURR->x);
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

t_map			*ft_new_map(t_coord *coord)
{
	t_map		*new;

	if (!(new = ft_memalloc(sizeof(t_map))))
		exit(0);
	new->x = coord->x;
	new->y = coord->y;
	if (!(new->map = ft_memalloc(sizeof(char *) * new->y + 1)))
		exit(0);
	(new->map)[new->y] = 0;
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

t_grid			*ft_new_grid(t_data *data)
{
	t_grid		*new;

	if (!(new = ft_memalloc(sizeof(t_grid))))
		exit(0);
	new->x = (WIN_X - BORDER * 2) / SIZE;
	new->y = (WIN_Y - BORDER * 2) / SIZE;
	new->rect = ft_new_rect(ft_new_coord(BORDER, BORDER),
			ft_new_coord(new->x * SIZE + BORDER,
				new->y * SIZE + BORDER), 0x00FFFFFF);
	new->size = SIZE;
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
	info->map_curr = ft_new_map(coord);
	info->map_prev = ft_new_map(coord);
	
	ft_strdel(&line);
	free(coord);
	
}

t_info			*ft_init_info(void)
{
	t_info		*new;

	if (!(new = ft_memalloc(sizeof(t_info))))
		exit(0);
	new->player = 0;
	new->ennemy = 0;
	new->map_curr = NULL;
	new->map_prev = NULL;
	new->piece = NULL;
	new->aim = NULL;
	new->t = 0;
	return (new);
}

t_mlx_env		*ft_init_mlx_env(void *mlx, int cell_size, int border)
{
	t_mlx_env	*new;

	if ((!(new = ft_memalloc(sizeof(t_mlx_env)))))
		exit(0);
	new->mlx = mlx;
	new->x = 0;
	new->y = 0;
	new->win = NULL;
	new->grid = NULL;
	new->border = border / 2;
	new->size = cell_size;
	return (new);
}

t_list			*ft_init_list()
{
	t_list		*new;

	if (!(new = ft_memalloc(sizeof(t_list))))
		exit(0);
	return (new);
}

t_data			*ft_init_data(void *mlx, int cell_size, int border)
{
	t_data		*new;

	if (!(new = ft_memalloc(sizeof(t_data))))
		exit(0);
	new->mlx_env = ft_init_mlx_env(mlx, cell_size, border);
	new->info = ft_init_info();
	new->list = NULL;
	return (new);
}

/*
** MAIN
*/

void			get_map_size(t_data *data, char *line)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	while (line[i] && (!(line[i] >= '0' && line[i] <= '9')))
		i++;
	x = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	y = ft_atoi(line + i);
	WIN_X = x * SIZE + BORDER * 2;
	WIN_Y = y * SIZE + BORDER * 2;
	MAP_CURR = ft_new_map(ft_new_coord(x, y));
	MAP_PREV = ft_new_map(ft_new_coord(x, y));
}

int				main(void)
{
	t_data		*data;
	char		*line;

	printf("| START |\n");

	data = ft_init_data(mlx_init(), 5, 40);

	// GET PLAYER
	printf("|	-> GETTING PLAYER...\n");
	get_next_line(0, &line);
	PLAYER = ((line[10] == '1') ? 'o' : 'x');
	ENNEMY = ((line[10] == '1') ? 'x' : 'o');
	printf("|		-> \033[34m%c\033[0m, \033[31m%c\033[0m\n", PLAYER, ENNEMY);
	ft_strdel(&line);

	// GET MAP_SIZE
	printf("|	-> GETTING MAP_SIZE...\n");
	get_next_line(0, &line);
	get_map_size(data, line);
	printf("|		-> [\033[32m%d\033[0m, \033[32m%d\033[0m]\n",
			(MAP_CURR)->x, (MAP_CURR)->y);
	printf("|		-> [\033[32m%d\033[0m, \033[32m%d\033[0m]\n",
			WIN_X, WIN_Y);
	ft_strdel(&line);

	// CREATE GRID
	printf("|	-> CREATING GRID...\n");
	GRID = ft_new_grid(data);
	printf("|		-> Size [%d, %d]\n",
			GRID_X, GRID_Y);
	printf("|		-> From [%d, %d] To [%d, %d]\n",
			GRID_RECT->coord1->x, GRID_RECT->coord1->y,
			GRID_RECT->coord2->x, GRID_RECT->coord2->y);

	WIN = mlx_new_window(MLX, WIN_X, WIN_Y, "Fill Her");

	// DISPLAY GRID
	printf("|	-> DISPLAYING GRID...\n");
	ft_display_grid(data);

	// SKIPING COLUMNS LINE
	get_next_line(0, &line);
	ft_strdel(&line);
	if (TURN)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}

	// GET MAP
	printf("|	-> GETTING MAP...\n");
	ft_get_map(data);

	// DISPLAY MAP
	/*
	int		i = 0;
	while (MAP[i])
	{
		printf("%s	%d\n", MAP[i], i);
		i++;
	}
	*/
	ft_display_map(data);
	printf("|	-> DISPLAYING MAP...\n");
	
	// DIFF MAP - MAP_PREV
	//printf("|	-> SPOTTING ENNEMIES...\n");

	// GET PIECE
	//printf("|	-> GETTING PIECE...\n");
	get_next_line(0, &line);
	
	// PROCESS
	//printf("|	-> PROCESSING...\n");

	mlx_hook(WIN, 2, 0, &ft_exit, 0);
	mlx_hook(WIN, 17, 0, &ft_exit, 0);
	//mlx_loop_hook(MLX, &ft_exit, 0);
	mlx_loop(MLX);

	printf("| END |\n");
	return (0);
}
