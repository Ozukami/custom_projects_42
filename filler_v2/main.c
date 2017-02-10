/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 23:52:54 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 04:48:21 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <stdio.h>

int			ft_absolute(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

t_place		*ft_new_place(int x, int y)
{
	t_place	*new;

	new = ft_memalloc(sizeof(t_place));
	new->x = x;
	new->y = y;
	return (new);
}

void		ft_add_place(t_place **list, t_place *new)
{
	new->next = *list;
	*list = new;
}

void		ft_get_piece_size(t_info **info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] > '0' && line[i] < '9')
		{
			(*info)->x_piece = ft_atoi(line + i);
			while (line[i] > '0' && line[i] < '9')
				i++;
			(*info)->y_piece = ft_atoi(line + i);
			break ;
		}
		i++;
	}
	(*info)->piece = ft_memalloc((sizeof(char *)) * ((*info)->x_piece + 1));
	((*info)->piece)[(*info)->x_piece] = 0;
}

void		ft_get_piece(t_info **info)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (i < (*info)->x_piece)
	{
		get_next_line(0, &line);
		((*info)->piece)[i] = ft_strdup(line);
		i++;
	}
}

int			ft_check_place(t_info *info, int x, int y, int verif)
{
	int		i;
	int		j;

	i = -1;
	if (x + info->x_piece > info->x_map || y + info->y_piece > info->y_map)
		return (0);
	while ((info->piece)[++i])
	{
		j = -1;
		while ((info->piece)[i][++j])
		{
			if ((info->piece)[i][j] != '.')
				if ((info->map)[i + x][j + y] != '.')
				{
					if ((info->map)[i + x][j + y] != info->player
							&& (info->map)[i + x][j + y] != info->player - 32)
						return (0);
					else if (verif++)
						return (0);
				}
		}
	}
	if (verif)
		return (1);
	return (0);
}

void		ft_find_place(t_info **info, t_place **list)
{
	int		x;
	int		y;

	x = 0;
	while (((*info)->map)[x])
	{
		y = 0;
		while (((*info)->map)[x][y])
		{
			if (ft_check_place(*info, x, y, 0))
				ft_add_place(list, ft_new_place(x, y));
			y++;
		}
		x++;
	}
}

void		ft_send_coord(int x, int y, t_place *list)
{
	if (x > -1 && y > -1)
		dprintf(1, "%d %d\n", x, y);
	else if (list)
		dprintf(1, "%d %d\n", list->x, list->y);
	else
		dprintf(1, "%d %d\n", 0, 0);
}

void		ft_get_place(t_info *info)
{
	t_coord	*coord;
	t_place	*list;
	t_place	*current;

	list = NULL;
	ft_find_place(&info, &list);
	coord = ft_new_coord(-1, -1);
	current = list;
	while (current)
	{
		if (info->x_side > -1 || info->y_side > -1)
		{
			if (ft_absolute(info->x_side - current->x) +
					ft_absolute(info->y_side - current->y) <
					ft_absolute(info->x_side - coord->x) +
					ft_absolute(info->y_side - coord->y))
			{
				coord->x = current->x;
				coord->y = current->y;
			}
		}
		current = current->next;
	}
	ft_send_coord(coord->x, coord->y, list);
}

void		ft_map_size(t_info **info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] > '0' && line[i] < '9')
		{
			(*info)->x_map = ft_atoi(line + i);
			while (line[i] > '0' && line[i] < '9')
				i++;
			(*info)->y_map = ft_atoi(line + i);
			return ;
		}
		i++;
	}
}

void		ft_wild_ennemy_appears(t_info **info)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if ((*info)->map_prev)
	{
		x = 0;
		while (((*info)->map)[x])
		{
			y = 0;
			while (((*info)->map)[x][y])
			{
				if (((*info)->map)[x][y] != ((*info)->map_prev)[x][y])
				{
					(*info)->x_side = x;
					(*info)->y_side = y;
					((*info)->map_prev)[x][y] = ((*info)->map)[x][y];
				}
				y++;
			}
			x++;
		}
	}
}

void		ft_get_map(t_info **info, int t)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < (*info)->x_map)
	{
		get_next_line(0, &line);
		if (!t)
			((*info)->map_prev)[i] = ft_strdup(ft_strsub(line, 4,
					(*info)->x_map));
		else
			free(((*info)->map)[i]);
		((*info)->map)[i] = ft_strdup(ft_strsub(line, 4, (*info)->x_map));
		i++;
	}
}

void		ft_process(t_info **info, int t)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (t++)
		{
			get_next_line(0, &line);
			get_next_line(0, &line);
			ft_get_map(info, t);
		}
		ft_wild_ennemy_appears(info);
		get_next_line(0, &line);
		ft_get_piece_size(info, line);
		ft_get_piece(info);
		ft_get_place(*info);
	}
}

int			main(void)
{
	t_info	*info;
	char	*line;

	get_next_line(0, &line);
	info = ft_new_info(((line[10] == '1') ? 'o' : 'x'));
	get_next_line(0, &line);
	ft_map_size(&info, line);
	info->map = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	info->map_prev = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	(info->map)[info->x_map] = 0;
	(info->map_prev)[info->x_map] = 0;
	get_next_line(0, &line);
	ft_get_map(&info, 0);
	ft_process(&info, 0);
	return (0);
}