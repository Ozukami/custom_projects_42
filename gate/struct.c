/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:37:47 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 11:52:53 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

/*
** INIT FUNCTIONS
*/

t_mlx	*ft_new_mlx(int x, int y, char *title)
{
	t_mlx	*new;

	new	= malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, x, y, title);
	new->x = x;
	new->y = y;
	new->pos_x = x / 2;
	new->pos_y = y / 2;
	new->draw = 1;
	new->color = 0x00000000;
	new->buts = NULL;
	new->player = NULL;
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

t_player	*ft_new_player(int x, int y, int size, char *name, int color)
{
	t_player	*new;

	new = malloc(sizeof(t_player));
	new->name = name;
	new->color = color;
	new->x = x;
	new->y = y;
	new->size = size;
	new->life = 3;
	return (new);
}

/*
** MOD FUNCTIONS
*/

void	ft_add_but(t_mlx **mlx, t_but *new_but)
{
	new_but->next = (*mlx)->buts;
	(*mlx)->buts = new_but;
}

/*
** DISPLAY FUNCTIONS
*/

void		ft_display_but(t_mlx *mlx)
{
	ft_fill_rectangle(mlx->mlx, mlx->win, (mlx->buts)->x, (mlx->buts)->y,
			(mlx->buts)->col, (mlx->buts)->line, (mlx->buts)->color);
	mlx_string_put(mlx->mlx, mlx->win, (mlx->buts)->x, (mlx->buts)->y,
			0x00000000, (mlx->buts)->title);
}

void		ft_hide_gate(t_mlx *mlx)
{
	ft_fill_rectangle(mlx->mlx, mlx->win, (mlx->buts)->x, (mlx->buts)->y,
			(mlx->buts)->col, (mlx->buts)->line, 0x00000000);
}

void		ft_display_player(t_mlx *mlx)
{
	ft_fill_rectangle(mlx->mlx, mlx->win, (mlx->player)->x, (mlx->player)->y,
			(mlx->player)->size, (mlx->player)->size, (mlx->player)->color);
}

void		ft_hide_player(t_mlx *mlx)
{
	ft_fill_rectangle(mlx->mlx, mlx->win, (mlx->player)->x, (mlx->player)->y,
			(mlx->player)->size, (mlx->player)->size, 0x00000000);
}
