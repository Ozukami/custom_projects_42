/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 06:29:27 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 12:12:37 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

int	ft_gate(t_mlx *mlx)
{
	if (((mlx->player)->x > (mlx->buts)->x
			&& (mlx->player)->x < (mlx->buts)->x + (mlx->buts)->col
			&& (mlx->player)->y > (mlx->buts)->y
			&& (mlx->player)->y < (mlx->buts)->y + (mlx->buts)->line)
			|| ((mlx->player)->x + (mlx->player)->size > (mlx->buts)->x
			&& (mlx->player)->x + (mlx->player)->size < (mlx->buts)->x + (mlx->buts)->col
			&& (mlx->player)->y + (mlx->player)->size > (mlx->buts)->y
			&& (mlx->player)->y + (mlx->player)->size < (mlx->buts)->y + (mlx->buts)->line))
		return (1);
	return (0);
}

/*
 ** HOOKS
 */

int	ft_move(int key, t_mlx **mlx)
{
	if (key == 53)
		exit(0);
	else if (key == 123 || key == 124 || key == 125 || key == 126)
	{
		ft_hide_player(*mlx);
		if (key == 123) // LEFT
			((*mlx)->player)->x -= 25;
		else if (key == 124) // RIGHT
			((*mlx)->player)->x += 25;
		else if (key == 125) // DOWN
			((*mlx)->player)->y += 25;
		else if (key == 126) // UP
			((*mlx)->player)->y -= 25;
		if (ft_gate(*mlx))
		{
			ft_hide_gate(*mlx);
			(*mlx)->buts = ((*mlx)->buts)->next;
			if ((*mlx)->buts)
				ft_display_but(*mlx);
			else
				exit(0);
		}
		ft_display_player(*mlx);
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
	return (1);
}

/*
 ** MAIN
 */

int	main(void)
{
	t_mlx		*mlx;
	int			r;

	mlx = ft_new_mlx(500, 500, "G A T E");
	ft_add_but(&mlx, ft_new_but(0, 0, 50, 50, 0x50FF0000, "GATE 5"));
	ft_add_but(&mlx, ft_new_but(200, 50, 50, 50, 0x0000FF00, "GATE 4"));
	ft_add_but(&mlx, ft_new_but(375, 210, 50, 50, 0x000000FF, "GATE 3"));
	ft_add_but(&mlx, ft_new_but(115, 390, 50, 50, 0x00FF00FF, "GATE 2"));
	ft_add_but(&mlx, ft_new_but(400, 130, 50, 50, 0x00FFFF00, "GATE 1"));
	ft_display_but(mlx);
	mlx->player = ft_new_player((mlx->x)/2, (mlx->y)/2, 10, "ozuk", 0x00F87D99);
	ft_display_player(mlx);
	r = mlx_key_hook(mlx->win, &ft_move, &mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
