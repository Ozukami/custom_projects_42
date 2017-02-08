/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:34:33 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 12:04:23 by apoisson         ###   ########.fr       */
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

typedef struct	s_player
{
	char	*name;
	int		color;
	int		x;
	int		y;
	int		size;
	int		life;
}				t_player;

typedef struct	s_but
{
	char	*title;
	int		x;
	int		y;
	int		col;
	int		line;
	int		color;
	struct s_but	*next;
}				t_but;

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
	t_but		*buts;
	t_player	*player;
}				t_mlx;

t_mlx	*ft_new_mlx(int x, int y, char *title);
t_but	*ft_new_but(int x, int y, int col, int line, int color, char *title);
t_player	*ft_new_player(int x, int y, int size, char *name, int color);

void	ft_add_but(t_mlx **mlx, t_but *new_but);
void	ft_display_but(t_mlx *mlx);
void	ft_hide_gate(t_mlx *mlx);
void	ft_display_player(t_mlx *mlx);
void	ft_hide_player(t_mlx *mlx);

void	ft_put_line(void *mlx, void *win, int x, int y, int value, int dir,
		int color);
void	ft_fill_rectangle(void *mlx, void *win, int x, int y,
		int col, int line, int color);

int		ft_move(int key, t_mlx **mlx);

#endif
