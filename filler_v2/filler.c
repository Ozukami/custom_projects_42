/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:41:35 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/26 07:44:47 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** FREE FUN
*/

void			ft_free_map(t_map *map)
{
	int			i;

	i = 0;
	while (i < map->y)
		free((map->map)[i++]);
	free((map->map)[i]);
}

void			ft_free_list(t_place *place)
{
	if (place->next)
		ft_free_list(place->next);
	place->next = NULL;
	place->prev = NULL;
	free(place);
}

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
** DISPLAY FUN
*/

void			ft_display_map(t_data *data)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	while (++y < ((MAP_CURR)->x))
	{
		x = -1;
		while (++x < (MAP_CURR)->y)
		{
			if (MAP[y][x] == 'O' || MAP[y][x] == 'o')
				color = 0x00FF0000;
			else if (MAP[y][x] == 'X' || MAP[y][x] == 'x')
				color = 0x000000FF;
			else
				color = 0x0000FF00;
			ft_fill_rect(data, ft_new_rect(ft_new_coord(
							ft_get_i_grid(x, data) + 1,
							ft_get_i_grid(y, data) + 1),
						ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1), color));
		}
	}
}

void			ft_display_grid(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (y < (((WIN_X - 2 * BORDER)) / CELL_SIZE) + 1)
	{
		dprintf(2, "%d ", y);
		ft_draw_line(data,
				ft_new_coord(BORDER, (y * CELL_SIZE) + BORDER),
				ft_new_coord(WIN_Y - (2 * BORDER), RIGHT),
				0x00FFFFFF);
		y++;
	}
		dprintf(2, "\n");
	x = 0;
	while (x < (((WIN_Y - 2 * BORDER)) / CELL_SIZE) + 1)
	{
		dprintf(2, "%d ", x);
		ft_draw_line(data,
				ft_new_coord((x * CELL_SIZE) + BORDER, BORDER),
				ft_new_coord(WIN_X - (2 * BORDER), DOWN),
				0x00FFFFFF);
		x++;
	}
		dprintf(2, "\n");
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
	while (i < (MAP_CURR)->x)
	{
		get_next_line(0, &line);
		dprintf(2, "\033[34m			|%s|\n", line);
		if (!(TURN))
			(MAP_PREV->map)[i] = ft_strsub(line, 4, MAP_CURR->y);
		else
			ft_strdel(&(MAP[i]));
		MAP[i] = ft_strsub(line, 4, MAP_CURR->y);
		free(line);
		i++;
	}
	TURN++;
}

void			ft_get_map_size(t_data *data, char *line)
{
	int			i;
	int			x;
	int			y;

	dprintf(2, "\033[34mget_map_size | Line = %s\n", line);
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

void			ft_get_piece(t_data *data)
{
	int			i;
	char		*line;

	line = NULL;
	i = 0;
	while (i < PIECE->y)
	{
		get_next_line(0, &line);
		(PIECE->map)[i] = ft_strdup(line);
		i++;
	}
}

void			ft_get_piece_size(t_data *data, char *line)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	while (line[i] && (!(line[i] >= '0' && line[i] <= '9')))
		i++;
	y = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	x = ft_atoi(line + i);
	ft_free_map(PIECE);
	PIECE = ft_new_map(ft_new_coord(x, y));
}

/*
** NEW FUN
*/

t_place			*ft_new_place(int x, int y)
{
	t_place		*new;

	if (!(new = ft_memalloc(sizeof(t_place))))
		exit(0);
	new->x = x;
	new->y = y;
	return (new);
}

t_map			*ft_new_map(t_coord *coord)
{
	t_map		*new;

	if (!(new = ft_memalloc(sizeof(t_map))))
		exit(0);
	new->x = coord->x;
	new->y = coord->y;
	if (new->x < 0 || new->y < 0)
	{
		new->map = NULL;
		return (new);
	}
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

t_info			*ft_init_info(void)
{
	t_info		*new;

	if (!(new = ft_memalloc(sizeof(t_info))))
		exit(0);
	new->player = 0;
	new->ennemy = 0;
	new->map_curr = NULL;
	new->map_prev = NULL;
	new->piece = ft_new_map(ft_new_coord(0, 0));
	new->aim = ft_new_map(ft_new_coord(-1, -1));
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
** PLACE FUN
*/

void			ft_add_place(t_data *data, t_place *new)
{
	new->next = LIST;
	LIST = new;
}

int				ft_check_place(t_data *data, int x, int y, int verif)
{
	int			i;
	int			j;

	i = -1;
	if (x + PIECE->x > MAP_CURR->x || y + PIECE->y > MAP_CURR->y)
		return (0);
	while ((PIECE->map)[++i])
	{
		j = -1;
		while ((PIECE->map)[i][++j])
		{
			if ((PIECE->map)[i][j] != '.' && MAP[i + x][j + y] != '.')
			{
				if (MAP[i + x][j + y] != PLAYER
						&& MAP[i + x][j + y] != PLAYER - 32)
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

void			ft_find_place(t_data *data)
{
	int			x;
	int			y;

	dprintf(2, "\033[31mfind place\n\033[0m");
	x = 0;
	while (MAP[x])
	{
		y = 0;
		while (MAP[x][y])
		{
			if (ft_check_place(data, x, y, 0))
			{
				dprintf(1, "%d %d\n", x, y);
				return ;
				//ft_add_place(data, ft_new_place(x, y));
			}
			y++;
		}
		x++;
	}
	dprintf(1, "%d %d\n", 0, 0);
}

void			ft_update_map(t_data *data, t_coord *coord)
{
	int			x;
	int			y;

	x = 0;
	while (MAP_PIECE[x])
	{
		y = 0;
		while (MAP_PIECE[x][y])
		{
			if (MAP_PIECE[x][y] == '*')
				ft_fill_rect(data, ft_new_rect(ft_new_coord(
								ft_get_i_grid(coord->x + x, data) + 1,
								ft_get_i_grid(coord->y + y, data) + 1),
							ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
							0x00ECE142));
			y++;
		}
		x++;
	}
}

void			ft_send_coord(t_data *data, t_coord *coord)
{
	if (coord->x > -1 && coord->y > -1)
		dprintf(1, "%d %d\n", coord->x, coord->y);
	else if (LIST)
	{
		dprintf(1, "%d %d\n", LIST->x, LIST->y);
		ft_update_map(data, coord);
	}
	else
		dprintf(1, "0 0\n");
}

void			ft_get_place(t_data *data)
{
	t_place		*current;
	t_coord		*coord;

	current = LIST;
	coord = ft_new_coord(-1, -1);
	while (current)
	{
		if (AIM->x > -1 || AIM->y > -1)
		{
			if (ft_absolute(AIM->x - current->x)
					+ ft_absolute(AIM->y - current->y)
					< ft_absolute(AIM->x - coord->x)
					+ ft_absolute(AIM->y - coord->y))
			{
				coord->x = current->x;
				coord->y = current->y;
			}
		}
		current = current->next;
	}
	ft_send_coord(data, coord);
}

/*
** MAIN PROCESS FUN
*/

void			ft_wild_ennemy_appears(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (MAP[y])
	{
		x = 0;
		while (MAP[y][x])
		{
			if (MAP[y][x] != ((MAP_PREV)->map)[y][x])
			{
				if (MAP[y][x] != PLAYER && MAP[y][x] != PLAYER - 32)
					ft_fill_rect(data, ft_new_rect(ft_new_coord(
									ft_get_i_grid(x, data) + 1,
									ft_get_i_grid(y, data) + 1),
								ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
								0x00FF00FF));
				if (MAP[y][x] == ENNEMY)
					AIM = ft_new_map(ft_new_coord(x, y));
				((MAP_PREV)->map)[y][x] = MAP[y][x];
			}
			x++;
		}
		y++;
	}
}

int				ft_process(t_data *data)
{
	char		*line;
	int			i;

	dprintf(2, "\033[34m	< %p >\n\033[0m", data);
	// SKIPING COLUMNS LINE
	get_next_line(0, &line);
	ft_strdel(&line);
	if (TURN)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
		//ft_free_list(LIST);
	}
	dprintf(2, "\033[34m%d\n\033[0m", MAP_CURR->x);
	dprintf(2, "\033[34m%d\n\033[0m", MAP_CURR->y);

	// GET MAP
	dprintf(2, "\033[34m|	-> GETTING MAP...\n\033[0m");
	ft_get_map(data);
	dprintf(2, "\033[34m|		-> MAP OK\n\033[0m");

	// DISPLAY MAP
	dprintf(2, "\033[34m|	-> DISPLAYING MAP...\n\033[0m");
	i = 0;
	while (MAP[i])
		dprintf(2, "		|%s|\n", MAP[i++]);
	ft_display_map(data);
	dprintf(2, "\033[34m|		-> DISPLAY OK\n\033[0m");
	
	// DIFF MAP - MAP_PREV
	dprintf(2, "\033[34m|	-> SPOTTING ENNEMIES...\n\033[0m");
	ft_wild_ennemy_appears(data);
	if (AIM->x > -1 && AIM->y > -1)
	{
		dprintf(2, "\033[34m|		< LAST ENNEMY SAW ON [%d,%d] >\n\033[0m", AIM->x, AIM->y);
		ft_fill_rect(data, ft_new_rect(ft_new_coord(
						ft_get_i_grid(AIM->x, data) + 1,
						ft_get_i_grid(AIM->y, data) + 1),
					ft_new_coord(CELL_SIZE - 2, CELL_SIZE - 1),
					0x00000000));
	}

	// GET PIECE
	dprintf(2, "\033[34m|	-> GETTING PIECE...\n\033[0m");
	get_next_line(0, &line);
	dprintf(2, "\033[34m%s\n\033[0m", line);
	ft_get_piece_size(data, line);
	ft_get_piece(data);

	dprintf(2, "\033[34m|	-> DISPLAYING PIECE...\n\033[0m");
	i = 0;
	while (MAP_PIECE[i])
		dprintf(2, "\033[34m|		%s\n\033[0m", MAP_PIECE[i++]);

	// PROCESS
	dprintf(2, "\033[34m|	-> PROCESSING...\n\033[0m");
	
	// FIND VALID PLACES
	dprintf(2, "\033[34m|		-> FINDING VALID PLACES...\n\033[0m");
	ft_find_place(data);
	sleep(1);

	/*
	// GET BEST PLACE
	dprintf(2, "\033[34m|		-> GETTING BEST PLACE...\n\033[0m");
	ft_get_place(data);

	// DISPLAY SOLUTION
	dprintf(2, "\033[34m%d %d\n\033[0m", LIST->x, LIST->y);
	*/
	return (1);
}

int				ft_key_handler(int key, t_data *data)
{
	(void)data;
	if (key == 53)
		ft_exit();
	/*
	else
		ft_process(key, data);
		*/
	return (0);
}

int				ft_exit(void)
{
	exit(0);
	return (0);
}

int				ft_test(t_data *data)
{
	dprintf(2, "\033[34m%p\n\033[0m", data);
	return (1);
}

/*
** MAIN
*/

int				main(void)
{
	t_data		*data;
	char		*line;

	dprintf(2, "\033[34m| START |\n\033[0m");

	data = ft_init_data(mlx_init(), 5, 40);

	// GET PLAYER
	dprintf(2, "\033[34m|	-> GETTING PLAYER...\n\033[0m");
	get_next_line(0, &line);
	PLAYER = ((line[10] == '1') ? 'o' : 'x');
	ENNEMY = ((line[10] == '1') ? 'x' : 'o');
	dprintf(2, "\033[34m|		-> \033[34m%c\033[0m, \033[31m%c\033[0m\n", PLAYER, ENNEMY);
	ft_strdel(&line);

	// GET MAP_SIZE
	dprintf(2, "\033[34m|	-> GETTING MAP_SIZE...\n\033[0m");
	get_next_line(0, &line);
	ft_get_map_size(data, line);
	dprintf(2, "\033[34m|		-> [\033[34m%d\033[0m, \033[34m%d\033[0m]\n\033[0m",
			(MAP_CURR)->x, (MAP_CURR)->y);
	dprintf(2, "\033[34m|		-> [\033[34m%d\033[0m, \033[34m%d\033[0m]\n\033[0m",
			WIN_X, WIN_Y);
	ft_strdel(&line);

	// CREATE GRID
	dprintf(2, "\033[34m|	-> CREATING GRID...\n\033[0m");
	GRID = ft_new_grid(data);
	dprintf(2, "\033[34m|		-> Size [%d, %d]\n\033[0m",
			GRID_X, GRID_Y);
	dprintf(2, "\033[34m|		-> From [%d, %d] To [%d, %d]\n\033[0m",
			GRID_RECT->coord1->x, GRID_RECT->coord1->y,
			GRID_RECT->coord2->x, GRID_RECT->coord2->y);

	WIN = mlx_new_window(MLX, WIN_X, WIN_Y, "Fill Her");

	// DISPLAY GRID
	dprintf(2, "\033[34m|	-> DISPLAYING GRID...\n\033[0m");
	ft_display_grid(data);
	dprintf(2, "\033[34m|		-> DISPLAY OK\n\033[0m");

	mlx_hook(WIN, 2, 0, &ft_key_handler, data);
	mlx_hook(WIN, 17, 0, &ft_exit, 0);

	mlx_loop_hook(MLX, &ft_process, data);
	//mlx_loop_hook(MLX, &ft_exit, 0);
	mlx_loop(MLX);

	dprintf(2, "\033[34m| END |\n\033[0m");
	return (0);
}
