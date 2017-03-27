/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:35:11 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 04:34:50 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** FREE FUNCTIONS
*/

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_strdel(&(map[i]));
		i++;
	}
}

void	free_rect(t_rect *rect)
{
	free(R_1);
	free(R_2);
}

void	free_info(t_info *info)
{
	free_map(info->map);
	free_map(info->map_prev);
	free_map(info->piece);
	free(info);
}

void	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free_rect(mlx->grid);
	free(mlx->mlx);
	free(mlx);
}

void	free_data(t_data *data)
{
	free_info(INFO);
	free_mlx(MLX);
	free(data);
}
