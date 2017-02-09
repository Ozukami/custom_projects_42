/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 06:29:27 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 00:03:50 by apoisson         ###   ########.fr       */
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
	int	x_map;
	int	y_map;

	x_map = ft_get_i_map(((*mlx)->player)->x, 20, 25);
	y_map = ft_get_i_map(((*mlx)->player)->y, 100, 25);
	printf("Actual pos : [%d,%d]", x_map, y_map);
	//printf("[%d,%d]\n", ((*mlx)->player)->x, ((*mlx)->player)->y);
	if (!ft_check_grid_bounds((*mlx)->player, (*mlx)->grid, dir))
	{
		ft_display_player(*mlx);
		mlx_do_sync((*mlx)->mlx);
		printf(" >< Can't escape the map without passing the G A T E S\n");
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
	x_map = ft_get_i_map(((*mlx)->player)->x, 20, 25);
	y_map = ft_get_i_map(((*mlx)->player)->y, 100, 25);
	printf(" -> [%d,%d]\n", x_map, y_map);
	return (1);
}

/*
 ** HOOKS
 */

int	ft_key_release_event_handler(int key, t_mlx **mlx)
{
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
	//printf("Key Released : %d (not binded)\n", key);
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

int	ft_key_pressed_event_handler(int key, t_mlx **mlx)
{
	mlx_do_key_autorepeaton(*mlx);
	if (key == ECHAP_KEY)
	{
		printf("Key Pressed : %d (exit ->[])\n", key);
		exit(0);
	}
	if (key == LEFT_KEY || key == RIGHT_KEY || key == UP_KEY || key == DOWN_KEY)
	{
		ft_hide_player(*mlx);
		if (key == LEFT_KEY)
			ft_move(mlx, LEFT);
		else if (key == RIGHT_KEY)
			ft_move(mlx, RIGHT);
		else if (key == DOWN_KEY)
			ft_move(mlx, DOWN);
		else if (key == UP_KEY)
			ft_move(mlx, UP);
	}
	else
		printf("Key Pressed : %d (not binded)\n", key);
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
	//ft_add_player(mlx, );
	mlx->player = ft_new_player((mlx->x)/2 + 1, (mlx->y)/2 - 8, 22, "ozuk", 0x00F87D99);
	int	x_map = ft_get_i_map((mlx->player)->x - 1, 20, 25);
	int	y_map = ft_get_i_map((mlx->player)->y - 1, 100, 25);
	//printf("START\n[%d,%d]\n", x_map, y_map);
	//(mlx->map)[][] = ;
	ft_display_grid(mlx);
	ft_display_player(mlx);
	mlx_key_hook(mlx->win, &ft_key_release_event_handler, &mlx);
	mlx_mouse_hook(mlx->win, &ft_attack, &mlx);
	mlx_hook(mlx->win, 2, 0, &ft_key_pressed_event_handler, &mlx);
	mlx_hook(mlx->win, 17, 0, &ft_exit, &mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
