/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:34:33 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 09:20:33 by apoisson         ###   ########.fr       */
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
 * Key codes
 */

# define ECHAP_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126

# define SPACE_KEY 49
# define TAB_KEY 48
# define CAPSLOCK_KEY 272
# define RETURN_KEY 36
# define SHIFT_LEFT_KEY 257
# define SHIFT_RIGHT_KEY 258
# define CTRL_LEFT_KEY 257
# define CTRL_RIGHT_KEY 269
# define OPT_LEFT_KEY 261
# define OPT_RIGHT_KEY 262
# define CMD_LEFT_KEY 259
# define CMD_RIGHT_KEY 260
# define DEL_KEY 51

# define A_KEY 0
# define B_KEY 11
# define C_KEY 8
# define D_KEY 2
# define E_KEY 14
# define F_KEY 3
# define G_KEY 5
# define H_KEY 4
# define I_KEY 34
# define J_KEY 38
# define K_KEY 40
# define L_KEY 37
# define M_KEY 46
# define N_KEY 45
# define O_KEY 31
# define P_KEY 35
# define Q_KEY 12
# define R_KEY 15
# define S_KEY 1
# define T_KEY 17
# define U_KEY 32
# define V_KEY 9
# define W_KEY 13
# define X_KEY 7
# define Y_KEY 16
# define Z_KEY 6

# define CLAV_0_KEY 29
# define CLAV_1_KEY 18
# define CLAV_2_KEY 19
# define CLAV_3_KEY 20
# define CLAV_4_KEY 21
# define CLAV_5_KEY 23
# define CLAV_6_KEY 22
# define CLAV_7_KEY 26
# define CLAV_8_KEY 28
# define CLAV_9_KEY 25

# define COMA_KEY 43
# define POINT_KEY 47
# define SLAH_KEY 44
# define SEMICOL_KEY 41
# define APO_KEY 39
# define BACKSLASH_KEY 42
# define O_BRACKET_KEY 33
# define C_BRACKET_KEY 30
# define EQUAL_KEY 24
# define MINUS_KEY 27
# define TILD_KEY 50

# define DELETE_KEY 117
# define END_KEY 119
# define FN_KEY 279
# define HOME_KEY 115
# define UP_PAGE_KEY 116
# define DOWN_PAGE_KEY 121

/*
 ** PAVER NUM
 */

# define NUM_0_KEY 82
# define NUM_1_KEY 83
# define NUM_2_KEY 84
# define NUM_3_KEY 85
# define NUM_4_KEY 86
# define NUM_5_KEY 87
# define NUM_6_KEY 88
# define NUM_7_KEY 89
# define NUM_8_KEY 91
# define NUM_9_KEY 92

# define NUM_POINT_KEY 65
# define NUM_ENTER_KEY 76
# define NUM_PLUS_KEY 69
# define NUM_MINUS_KEY 78
# define NUM_MULTI_KEY 67
# define NUM_DIVIDE_KEY 75
# define NUM_EQUAL_KEY 81
# define NUM_CLEAR_KEY 71

/*
 * Move Direction
 */

# define LEFT 1
# define RIGHT 2
# define DOWN 3
# define UP 4

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

int			ft_key_event_handler(int key, t_mlx **mlx);

#endif
