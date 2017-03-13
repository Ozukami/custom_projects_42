/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:27:04 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/13 05:07:23 by apoisson         ###   ########.fr       */
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

t_coord				*ft_new_coord(int x, int y);
t_rect				*ft_new_rect(t_coord *coord1, t_coord *coord2,
		int color);
t_grid				*ft_new_grid(int x, int y, int border, int cell_size);
int					ft_get_i_map(int i, t_data *data);
int					ft_get_i_grid(int i, t_data *data);

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
