/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:27:04 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/26 04:02:59 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h> //

# define DOWN		0
# define RIGHT		1
# define UP			2
# define LEFT		3

# define MLX_ENV	(data->mlx_env)
# define MLX		((data->mlx_env)->mlx)
# define WIN		((data->mlx_env)->win)
# define WIN_X		((data->mlx_env)->x)
# define WIN_Y		((data->mlx_env)->y)
# define GRID		((data->mlx_env)->grid)
# define BORDER		((data->mlx_env)->border)
# define SIZE		((data->mlx_env)->size)

# define GRID_RECT	(((data->mlx_env)->grid)->rect)
# define CELL_SIZE	(((data->mlx_env)->grid)->size)
# define GRID_X		(((data->mlx_env)->grid)->x)
# define GRID_Y		(((data->mlx_env)->grid)->y)

# define R_X1		((rect->coord1)->x)
# define R_Y1		((rect->coord1)->y)
# define R_X2		((rect->coord2)->x)
# define R_Y2		((rect->coord2)->y)
# define R_COLOR	(rect->color)

# define INFO		(data->info)
# define PLAYER		((data->info)->player)
# define ENNEMY		((data->info)->ennemy)
# define MAP_CURR	((data->info)->map_curr)
# define MAP		(((data->info)->map_curr)->map)
# define MAP_PREV	((data->info)->map_prev)
# define PIECE		((data->info)->piece)
# define MAP_PIECE	(((data->info)->piece)->map)
# define AIM		((data->info)->aim)
# define TURN		((data->info)->t)

# define I_MAP_CURR	(((info)->map_curr)->map)
# define I_MAP_PREV	(((info)->map_prev)->map)

# define LIST		(data->list)
# define NEXT		((data->list)->next)
# define PREV		((data->list)->prev)
# define PLACE_X	((data->list)->x)
# define PLACE_Y	((data->list)->y)

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_rect
{
	t_coord			*coord1;
	t_coord			*coord2;
	int				color;
}					t_rect;

typedef struct		s_grid
{
	t_rect			*rect;
	int				size;
	int				x;
	int				y;
}					t_grid;

typedef struct		s_mlx_env
{
	void			*mlx;
	void			*win;
	int				x;
	int				y;
	t_grid			*grid;
	int				border;
	int				size;
}					t_mlx_env;

typedef struct		s_map
{
	char			**map;
	int				x;
	int				y;
}					t_map;

typedef struct		s_info
{
	char			player;
	char			ennemy;
	t_map			*map_curr;
	t_map			*map_prev;
	t_map			*piece;
	t_map			*aim;
	int				t;
}					t_info;

typedef struct		s_place
{
	struct s_place	*next;
	struct s_place	*prev;
	int				x;
	int				y;	
}					t_place;

typedef struct		s_data
{
	t_info			*info;
	t_mlx_env		*mlx_env;
	t_place			*list;
}					t_data;

/*
** FREE FUN
*/

void				ft_free_map(t_map *map);

/*
** DRAW FUN
*/

void				ft_draw_line(t_data *data, t_coord *pos_ini,
		t_coord *charac, int color);
void				ft_fill_rect(t_data *data, t_rect *rect);
void				ft_draw_rect(t_data *data, t_rect *rect);

/*
** DISPLAY FUN
*/

void				ft_display_grid(t_data *data);
void				ft_display_map(t_data *data);

/*
** GET FUN
*/

int					ft_get_i_grid(int i, t_data *data);
int					ft_get_i_map(int i, t_data *data);
void				ft_get_map(t_data *data);
void				ft_get_map_size(t_data *data, char *line);
void				ft_get_piece(t_data *data);
void				ft_get_piece_size(t_data *data, char *line);

/*
** NEW FUN
*/

t_map				*ft_new_map(t_coord *coord);
t_coord				*ft_new_coord(int x, int y);
t_rect				*ft_new_rect(t_coord *coord1, t_coord *coord2,
		int color);
t_grid				*ft_new_grid(t_data *data);

/*
** INIT FUN
*/

t_info				*ft_init_info(void);
t_mlx_env			*ft_init_mlx_env(void *mlx, int cell_size, int border);
t_list				*ft_init_list();
t_data				*ft_init_data(void *mlx, int cell_size, int border);

/*
** MAIN FUN
*/

int					ft_process(t_data *data);
int					ft_key_handler(int key, t_data *data);
int					ft_exit(void);

/*
t_mlx				*ft_new_mlx(int x, int y, char *title);
int					ft_get_i_map(int i, int i_border, int size);
int					ft_get_i_grid(int i, int i_border, int size);
void				ft_display_player(t_mlx *mlx);
void				ft_hide_player(t_mlx *mlx);
void				ft_display_grid(t_mlx *mlx);
void				ft_draw_line(t_mlx *mlx, int x, int y, int value,
		int dir, int color);
void				ft_fill_rectangle(t_mlx *mlx, int x, int y,
		int col, int line, int color);
void				ft_fill_square(t_mlx *mlx, int x, int y,
		int size, int color);
void				ft_draw_rectangle(t_mlx *mlx, int x, int y,
		int col, int line, int color);
void				ft_draw_square(t_mlx *mlx, int x, int y,
		int size, int color);
int					ft_key_event_handler(int key, t_mlx **mlx);
t_info				*ft_new_info(char p);
t_place				*ft_new_place(int x, int y);
void				ft_add_place(t_place **list, t_place *new);
int					ft_check_place(t_info *info, int x, int y, int verif);
t_coord				*ft_get_place(t_info *info);
t_coord				*ft_new_coord(int x, int y);
void				ft_free_coord(t_coord **coord);
t_data				*ft_new_data(t_info *info, t_mlx *mlx);
t_rect				*ft_new_rect(t_coord *coord1, t_coord *coord2, int color);
*/

#endif
