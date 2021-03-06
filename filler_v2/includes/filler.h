/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:27:04 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 23:34:54 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "mlx.h"

# define BORDER			20
# define CELL_SIZE		5

# define INFO			(data->info)
# define D_MAP			(data->info->map)
# define MAP			(info->map)
# define MAP_X			(info->x_map)
# define MAP_Y			(info->y_map)
# define D_MAP_PREV		(data->info->map_prev)
# define MAP_PREV		(info->map_prev)
# define D_PIECE		(data->info->piece)
# define PIECE			(info->piece)
# define PIECE_X		(info->x_piece)
# define PIECE_Y		(info->y_piece)

# define MLX			(data->mlx)
# define D_MLX_X		(data->mlx->x_size)
# define D_MLX_Y		(data->mlx->y_size)
# define D_MLX			(data->mlx->mlx)
# define D_WIN			(data->mlx->win)
# define WIN			(mlx->win)

# define DIRECTION		(charac->y)

# define RIGHT			1
# define LEFT			3
# define DOWN			0
# define UP				2

# define R_COLOR		(rect->color)

# define R_1			(rect->coord1)
# define R_X1			(rect->coord1->x)
# define R_Y1			(rect->coord1->y)

# define R_2			(rect->coord2)
# define R_X2			(rect->coord2->x)
# define R_Y2			(rect->coord2->y)

# define C_X			(coord->x)
# define C_Y			(coord->y)

# define I_GRID(a, b, c)	ft_get_i_grid(a, b, c)

# define SPEED			(data->speed)

typedef struct			s_info
{
	char				player;
	char				**map;
	int					x_map;
	int					y_map;
	char				**map_prev;
	int					x_map_prev;
	int					y_map_prev;
	char				**piece;
	int					x_piece;
	int					y_piece;
	int					x_side;
	int					y_side;
	int					t;
}						t_info;

typedef struct			s_place
{
	struct s_place		*next;
	int					x;
	int					y;
}						t_place;

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_rect
{
	t_coord				*coord1;
	t_coord				*coord2;
	int					color;
}						t_rect;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	int					x_size;
	int					y_size;
	int					bg_color;
	t_rect				*grid;
}						t_mlx;

typedef struct			s_data
{
	t_info				*info;
	t_mlx				*mlx;
	int					speed;
}						t_data;

void					ft_display_new_piece(t_data *data);
void					ft_display_map(t_data *data);
int						ft_exit(t_data *data);
int						ft_key_handler(int key, t_data *data);
void					ft_fill_rectangle(t_data *data, t_rect *rect);
void					ft_draw_rectangle(t_data *data, t_rect *rect);
void					ft_display_grid(t_data *data);
void					free_map(char **map);
void					free_info(t_info *info);
void					free_mlx(t_mlx *mlx);
void					free_data(t_data *data);
void					free_list(t_place **list);
t_info					*ft_new_info(void);
void					ft_get_piece_size(t_info *info, char *line);
void					ft_get_piece(t_info *info);
void					ft_get_map_size(t_info *info);
void					ft_get_map(t_info *info, int t);
int						ft_update_map(t_data *data);
int						ft_check_place(t_info *info, int x, int y, int verif);
void					ft_find_place(t_info *info, t_place **list);
t_coord					*ft_get_place(t_info *info);
void					ft_display_coord(int x, int y);
t_coord					*ft_new_coord(int x, int y);
t_rect					*ft_new_rect(t_coord *coord1,
		t_coord *coord2, int color);
t_mlx					*ft_new_mlx(int x, int y, char *title);
t_data					*ft_new_data(t_info *info, t_mlx *mlx);
t_place					*ft_new_place(int x, int y);
int						ft_get_i_map(int i, int i_border, int size);
int						ft_get_i_grid(int i, int i_border, int size);
void					ft_skip_n_line(int n);
void					ft_set_coord(t_coord *coord, int x, int y);
void					ft_add_place(t_place **list, t_place *new);
void					ft_wild_ennemy_appears(t_data *data);

#endif
