/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:27:04 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 03:30:39 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h> //
# include <fcntl.h>

typedef struct	s_info
{
	char		player;
	char		**map;
	int			x_map;
	int			y_map;
	char		**map_prev;
	int			x_map_prev;
	int			y_map_prev;
	char		**piece;
	int			x_piece;
	int			y_piece;
	int			x_side;
	int			y_side;
}				t_info;

typedef struct	s_place
{
	struct s_place	*next;
	struct s_place	*prev;
	int				x;
	int				y;	
}				t_place;

t_info			*ft_new_info(char p);
t_place			*ft_new_place(int x, int y);
void			ft_add_place(t_place **list, t_place *new);

int				ft_check_place(t_info *info, int x, int y);
void			ft_get_place(t_info *info, int fd);
void			ft_get_value(t_info *info, t_place place, int fd);

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

t_coord			*ft_new_coord(int x, int y);
void			ft_free_coord(t_coord **coord);

typedef struct	s_rect
{
	t_coord		*coord1;
	t_coord		*coord2;
	int			color;
}				t_rect;

t_rect		*ft_new_rect(t_coord *coord1, t_coord *coord2, int color);

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			x_size;
	int			y_size;
	int			bg_color;
	int			**map;
	t_rect		*grid;
}				t_mlx;

t_mlx		*ft_new_mlx(t_coord *couple, char *title);

int			ft_get_i_map(int i, int i_border, int size);
int			ft_get_i_grid(int i, int i_border, int size);

void		ft_display_player(t_mlx *mlx);
void		ft_hide_player(t_mlx *mlx);
void		ft_display_grid(t_mlx *mlx);

void		ft_draw_line(t_mlx *mlx, int x, int y, int value,
		int dir, int color);
void		ft_fill_rectangle(t_mlx *mlx, int x, int y,
		int col, int line, int color);
void		ft_fill_square(t_mlx *mlx, int x, int y,
		int size, int color);
void		ft_draw_rectangle(t_mlx *mlx, int x, int y,
		int col, int line, int color);
void		ft_draw_square(t_mlx *mlx, int x, int y,
		int size, int color);

int			ft_key_event_handler(int key, t_mlx **mlx);

#endif
