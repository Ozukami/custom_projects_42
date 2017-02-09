/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:34:33 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 07:43:07 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GATE_H

# define GATE_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/*
 * x = abscisses
 * y = ordonnees
 */

typedef struct	s_rect
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}				t_rect;

typedef struct	s_player
{
	char	*name;
	int		color;
	int		x;
	int		y;
	int		size;
	int		life;
}				t_player;

typedef struct	s_gate
{
	char	*title;
	int		x;
	int		y;
	int		col;
	int		line;
	int		color;
	struct s_gate	*next;
}				t_gate;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	int			pos_x;
	int			pos_y;
	int			draw;
	int			color;
	t_gate		*gates;
	t_player	*player;
	t_rect		*grid;
}				t_mlx;

t_mlx		*ft_new_mlx(int x, int y, char *title);
t_player	*ft_new_player(int x, int y, int size, char *name, int color);
t_rect		*ft_new_rect(int x1, int y1, int x2, int y2);
t_gate		*ft_new_gate(int x, int y, int col, int line,
		int color, char *title);
void		ft_add_gate(t_mlx **mlx, t_gate *new_gate);

void		ft_display_gate(t_mlx *mlx);
void		ft_hide_gate(t_mlx *mlx);
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

int		ft_key_event_handler(int key, t_mlx **mlx);

#endif
