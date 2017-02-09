/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 06:29:27 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 07:43:10 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gate.h"

int	ft_chek_collision(t_player *player, t_rect *rect, int dir)
{
	if ((player->x >= rect->x1
			&& player->x <= rect->x2
			&& player->y >= rect->y1
			&& player->y <= rect->y2)
			|| (player->x + player->size >= rect->x1
			&& player->x + player->size <= rect->x2
			&& player->y + player->size >= rect->y1
			&& player->y + player->size <= rect->y2))
		return (1);
	return (0);
}

int	ft_check_grid_bounds(t_player *player, t_rect *rect, int dir)
{
	if (dir == 1 && player->x - player->size >= rect->x1)
		return (1);
	if (dir == 2 && player->x + (player->size * 2) <= rect->x2)
		return (1);
	if (dir == 3 && player->y + (player->size * 2) <= rect->y2)
		return (1);
	if (dir == 4 && player->y - player->size >= rect->y1)
		return (1);
	return (0);
}

int	ft_gate(t_mlx *mlx)
{
	if (((mlx->player)->x >= (mlx->gates)->x
			&& (mlx->player)->x <= (mlx->gates)->x + (mlx->gates)->col
			&& (mlx->player)->y >= (mlx->gates)->y
			&& (mlx->player)->y <= (mlx->gates)->y + (mlx->gates)->line)
			|| ((mlx->player)->x + (mlx->player)->size >= (mlx->gates)->x
			&& (mlx->player)->x + (mlx->player)->size <= (mlx->gates)->x + (mlx->gates)->col
			&& (mlx->player)->y + (mlx->player)->size >= (mlx->gates)->y
			&& (mlx->player)->y + (mlx->player)->size <= (mlx->gates)->y + (mlx->gates)->line))
		return (1);
	return (0);
}

int	ft_move(t_mlx **mlx, int dir)
{
	int		i;

	//printf("[%d,%d]\n", ((*mlx)->player)->x, ((*mlx)->player)->y);
	if (!ft_check_grid_bounds((*mlx)->player, (*mlx)->grid, dir))
	{
		ft_display_player(*mlx);
		mlx_do_sync((*mlx)->mlx);
		return (0);
	}
	i = 0;
	while (i < 5)
	{
		ft_hide_player(*mlx);
		((*mlx)->player)->x -= ((dir == 1) ? 5 : 0);
		((*mlx)->player)->x += ((dir == 2) ? 5 : 0);
		((*mlx)->player)->y += ((dir == 3) ? 5 : 0);
		((*mlx)->player)->y -= ((dir == 4) ? 5 : 0);
		ft_display_player(*mlx);
		mlx_do_sync((*mlx)->mlx);
		i++;
	}
	ft_draw_rectangle(*mlx, ((*mlx)->player)->x - 1, ((*mlx)->player)->y - 2,
			((*mlx)->player)->size + 3, ((*mlx)->player)->size + 3, 0x00FFFFFF);
	mlx_do_sync((*mlx)->mlx);
	return (1);
}

/*
 ** HOOKS
 */

int	ft_key_event_handler(int key, t_mlx **mlx)
{
	if (key == 53) // 53 = ECHAP
		exit(0);
	else if (key == 123 || key == 124 || key == 125 || key == 126)
	{
		ft_hide_player(*mlx);
		if (key == 123) // 123 = LEFT 1
			ft_move(mlx, 1);
		else if (key == 124) // 124 = RIGHT 2
			ft_move(mlx, 2);
		else if (key == 125) // 125 = DOWN 3
			ft_move(mlx, 3);
		else if (key == 126) // 126 = UP 4
			ft_move(mlx, 4);
		/*
		if (ft_gate(*mlx))
		{
			ft_hide_gate(*mlx);
			ft_display_player(*mlx);
			(*mlx)->gates = ((*mlx)->gates)->next;
			if ((*mlx)->gates)
				ft_display_gate(*mlx);
			else
				exit(0);
		}
		*/
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

int	ft_attack(int button, int x, int y, t_mlx **mlx)
{
	ft_fill_rectangle(*mlx, x - 12, y - 12, 24, 24, 0x00FF0000);
	mlx_do_sync((*mlx)->mlx);
	ft_fill_rectangle(*mlx, x - 12, y - 12, 24, 24, 0x00000000);
	return (2);
}

int	ft_exit(int key, t_mlx **mlx)
{
	exit(0);
	return (0);
}

/*
 ** MAIN
 */

int	main(void)
{
	t_mlx		*mlx;
	int			r;

	/*
	int	i = 600;
	while (i < 1200)
	{
		if ((i - 120) % 25 == 0)
			printf("y %d\n", i);
		else if ((i - 40) % 25 == 0)
			printf("		x %d\n", i);
		i += 5;
	}
	*/

	mlx = ft_new_mlx(1040, 820, "G A T E");
	mlx->player = ft_new_player((mlx->x)/2 + 1, (mlx->y)/2 - 8, 22, "ozuk", 0x00F87D99);
	ft_display_grid(mlx);
	ft_display_player(mlx);
	mlx_key_hook(mlx->win, &ft_key_event_handler, &mlx);
	mlx_mouse_hook(mlx->win, &ft_attack, &mlx);
	mlx_hook(mlx->win, 17, (1L<<17), &ft_exit, &mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
