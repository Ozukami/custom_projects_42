/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:37:47 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 07:43:09 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

/*
** INIT FUNCTIONS
*/

t_rect	*ft_new_rect(int x1, int y1, int x2, int y2)
{
	t_rect	*new;

	new = malloc(sizeof(t_rect));
	new->x1 = x1;
	new->y1 = y1;
	new->x2 = x2;
	new->y2 = y2;
	return (new);
}

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
	new->gates = NULL;
	new->player = NULL;
	new->grid = ft_new_rect(20, 100, x - 20, y - 20);
	return (new);
}

t_gate	*ft_new_gate(int x, int y, int col, int line, int color, char *title)
{
	t_gate	*new;

	new = malloc(sizeof(t_gate));
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

void	ft_add_gate(t_mlx **mlx, t_gate *new_gate)
{
	new_gate->next = (*mlx)->gates;
	(*mlx)->gates = new_gate;
}
