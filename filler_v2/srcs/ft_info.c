/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:40:25 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/27 02:42:37 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	get_player(void)
{
	char	*line;
	char	c;

	get_next_line(0, &line);
	c = ((line[10] == '1') ? 'o' : 'x');
	ft_strdel(&line);
	return (c);
}

t_info	*ft_new_info(void)
{
	t_info	*info;

	info = ft_memalloc(sizeof(t_info));
	info->player = get_player();
	info->map = NULL;
	info->x_map = 0;
	info->y_map = 0;
	info->map_prev = NULL;
	info->x_map_prev = 0;
	info->y_map_prev = 0;
	info->piece = NULL;
	info->x_piece = 0;
	info->y_piece = 0;
	info->x_side = -1;
	info->y_side = -1;
	info->t = 0;
	return (info);
}
