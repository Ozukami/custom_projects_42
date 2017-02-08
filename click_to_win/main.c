/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 06:29:27 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 10:04:19 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	v1 = 0;
int	v2 = 0;
int	v3 = 0;
int	v4 = 0;

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
	int			pos_x;
	int			pos_y;
	int			draw;
	int			color;
	t_but		*buts;
}				t_mlx;

/*
** CREATION DES STRUCTURES
*/

t_mlx	*ft_new_mlx(int x, int y, char *title)
{
	t_mlx	*new;

	new	= malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, x, y, title);
	new->pos_x = x / 2;
	new->pos_y = y / 2;
	new->draw = 1;
	new->color = 0x00000000;
	new->buts = NULL;
	return (new);
}

t_but	*ft_new_but(int x, int y, int col, int line, int color, char *title)
{
	t_but	*new;

	new = malloc(sizeof(t_but));
	new->title = title;
	new->x = x;
	new->y = y;
	new->col = col;
	new->line = line;
	new->color = color;
	new->next = NULL;
	return (new);
}

void	ft_add_but(t_mlx **mlx, t_but *new_but)
{
	new_but->next = (*mlx)->buts;
	(*mlx)->buts = new_but;
}

/*
** CREATION DE FORME
*/

void	ft_put_line(void *mlx, void *win, int x, int y, int value, int dir, int color)
{
	int	i;

	i = 0;
	while (i < value)
	{
		if (!dir)
			y++;
		if (dir == 1)
			x++;
		if (dir == 2)
			y--;
		if (dir == 3)
			x--;
		mlx_pixel_put(mlx, win, x, y, color);
		i++;
	}
}

void		ft_fill_rectangle(void *mlx, void *win, int x, int y,
		int col, int line, int color)
{
	int		i;

	i = 0;
	while (i < line)
	{
		ft_put_line(mlx, win, x, y + i, col, 1, color);
		i++;
	}	
}
void		ft_display_but(t_mlx *mlx)
{
	ft_fill_rectangle(mlx->mlx, mlx->win, (mlx->buts)->x, (mlx->buts)->y,
			(mlx->buts)->col, (mlx->buts)->line, (mlx->buts)->color);
	mlx_string_put(mlx->mlx, mlx->win, (mlx->buts)->x, (mlx->buts)->y,
			0x00000000, (mlx->buts)->title);
}

/*
** HOOKS
*/

int	ft_move(int key, t_mlx **mlx)
{
	mlx_pixel_put((*mlx)->mlx, (*mlx)->win, (*mlx)->pos_x,
			(*mlx)->pos_y, (*mlx)->color);
	if (key == 123)
	{
		//printf("Left (%d)\n", key);
		if ((*mlx)->draw)
			ft_put_line((*mlx)->mlx, (*mlx)->win,
					(*mlx)->pos_x, (*mlx)->pos_y, 25, 3, 0x00FFFFFF);
		(*mlx)->pos_x -= 25;
			v1++;
	}
	else if (key == 124)
	{
		//printf("Right (%d)\n", key);
		if ((*mlx)->draw)
			ft_put_line((*mlx)->mlx, (*mlx)->win,
					(*mlx)->pos_x, (*mlx)->pos_y, 25, 1, 0x00FFFFFF);
		(*mlx)->pos_x += 25;
			v2++;
	}
	else if (key == 125)
	{
		//printf("Down (%d)\n", key);
		if ((*mlx)->draw)
			ft_put_line((*mlx)->mlx, (*mlx)->win,
					(*mlx)->pos_x, (*mlx)->pos_y, 25, 0, 0x00FFFFFF);
		(*mlx)->pos_y += 25;
			v3++;
	}
	else if (key == 126)
	{
		//printf("Up (%d)\n", key);
		if ((*mlx)->draw)
			ft_put_line((*mlx)->mlx, (*mlx)->win,
					(*mlx)->pos_x, (*mlx)->pos_y, 25, 2, 0x00FFFFFF);
		(*mlx)->pos_y -= 25;
			v4++;
	}
	else if (key == 49)
	{
		if ((*mlx)->draw)
			(*mlx)->draw--;
		else
			(*mlx)->draw++;
	}
	else
		printf("Key (%d)\n", key);
	if (key == 53)
		exit(0);
	mlx_pixel_put((*mlx)->mlx, (*mlx)->win,
			(*mlx)->pos_x, (*mlx)->pos_y, 0x00FF0000);
	if ((*mlx)->draw)
		(*mlx)->color = 0x00FFFFFF;
	else
		(*mlx)->color = 0x00000000;
	return (1);
}

int	ft_try(int button, int x, int y, t_mlx **mlx)
{
	if (x >= ((*mlx)->buts)->x && x <= (((*mlx)->buts)->x + ((*mlx)->buts)->line)
			&& y >= ((*mlx)->buts)->y && y <= (((*mlx)->buts)->y + ((*mlx)->buts)->col))
	{
		ft_fill_rectangle((*mlx)->mlx, (*mlx)->win, ((*mlx)->buts)->x, ((*mlx)->buts)->y,
				((*mlx)->buts)->col, ((*mlx)->buts)->line, 0x00000000);
		((*mlx)->buts) = ((*mlx)->buts)->next;
		if ((*mlx)->buts)
			ft_display_but((*mlx));
		else
			exit(0);
	}
	return (1);
}

/*
** MAIN
*/

int	main(void)
{
	t_mlx	*mlx;
	int		r;

	mlx = ft_new_mlx(500, 500, "Main Window");
	ft_add_but(&mlx, ft_new_but(0, 0, 50, 50, 0x00FF0000, "B1"));
	ft_add_but(&mlx, ft_new_but(200, 50, 50, 50, 0x0000FF00, "B2"));
	ft_add_but(&mlx, ft_new_but(375, 210, 50, 50, 0x000000FF, "B3"));
	ft_add_but(&mlx, ft_new_but(115, 390, 50, 50, 0x00FF00FF, "B4"));
	ft_add_but(&mlx, ft_new_but(400, 130, 50, 50, 0x00FFFF00, "B5"));
	ft_display_but(mlx);
	r = mlx_key_hook(mlx->win, &ft_move, &mlx);
	r = mlx_mouse_hook(mlx->win, &ft_try, &mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
