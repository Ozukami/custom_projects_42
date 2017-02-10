/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 23:52:54 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/10 03:05:45 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <stdio.h>

int	debug = 0;
int	no_VM = 0;

int		ft_absolute(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	ft_display_map(char **map, int fd)
{
	int	i;

	i = 0;
	while (map[i])
	{
		dprintf(fd, "%s\n", map[i]);
		i++;
	}
}

void	ft_display_info(t_info *info, int fd)
{
	dprintf(fd, "Player : %c\n", info->player);
	dprintf(fd, "Map : %d %d\n", info->x_map, info->y_map);
	ft_display_map(info->map, fd);
	dprintf(fd, "Piece : %d %d\n", info->x_piece, info->y_piece);
	ft_display_map(info->piece, fd);
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

void		ft_get_value(t_info *info, t_place place, int fd)
{
	(void)info;
	(void)place;
	(void)fd;
}

int			ft_check_place(t_info *info, int x, int y, int fd)
{
	int		i;
	int		j;
	int		verif;

	i = 0;
	j = 0;
	verif = 0;
	if (x + info->x_piece > info->x_map
			|| y + info->y_piece > info->y_map)
	{
		//dprintf(fd, "	>> Failed : map out of bounds\n");
		return (0);
	}
	while ((info->piece)[i])
	{
		j = 0;
		while ((info->piece)[i][j])
		{
			if ((info->piece)[i][j] != '.')
			{
				if ((info->map)[i + x][j + y] != '.')
				{
					if ((info->map)[i + x][j + y] != info->player
							&& (info->map)[i + x][j + y] != info->player - 32)
					{
						//dprintf(fd, "	>> Failed : enemy found ! %c VS %c\n",
						//		info->player, (info->map)[i + x][j + y]);
						return (0);
					}
					else
					{
						if (verif++)
						{
							//dprintf(fd, "	>> Failed : too much TK\n");
							return (0);
						}
					}
				}
			}
			j++;
		}
		i++;
	}
	if (verif)
	{
		dprintf(fd, "	>> SUCCES !\n");
		return (1);
	}
	//dprintf(fd, "	>> Failed : not enough friends :(\n");
	return (0);
}	

void		ft_get_place(t_info *info, int fd)
{
	int		x;
	int		y;
	t_place	*list;
	t_place	*current;

	dprintf(fd, "> START\n");
	list = NULL;
	x = 0;
	while ((info->map)[x])
	{	
		y = 0;
		while ((info->map)[x][y])
		{
			//dprintf(fd, "	> CHECK at {%d,%d}", x, y);
			if (ft_check_place(info, x, y, fd))
			{
				//dprintf(fd, "		> OK");
				ft_add_place(&list, ft_new_place(x, y));
				//dprintf(fd, "	>> PLACED\n");
				//ft_get_value(info, list, fd);
			}
			y++;
		}
		x++;
	}
	dprintf(fd, "\n	> SOLUTIONS\n");
	x = -1;
	y = -1;
	current = list;
	while (current)
	{
		if (info->x_side > -1 || info->y_side > -1)
		{
			if (ft_absolute(info->x_side - current->x) +
					ft_absolute(info->y_side - current->y) <
					ft_absolute(info->x_side - x) +
					ft_absolute(info->y_side - y))
			{
				x = current->x;
				y = current->y;
			}
		}
		dprintf(fd, "		>%d %d\n", current->x, current->y);
		current = current->next;
	}
	//ft_display_map(info->map, fd);
	if (x > -1 && y > -1)
	{
		dprintf(fd, "			BEST		{%d %d}\n", x, y);
		dprintf(1, "%d %d\n", x, y);
		return ;
	}
	dprintf(fd, "> REP ?\n");
	if (list)
	{
		dprintf(1, "%d %d\n", list->x, list->y);
		dprintf(fd, "	%d %d\n", list->x, list->y);
	}
	else
	{
		dprintf(1, "%d %d\n", 0, 0);
		dprintf(fd, "	%d %d (FAILED)\n", 0, 0);
	}
	dprintf(fd, "> END\n");
}

void	ft_map_size(t_info **info, char *line)
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

int		main(void)
{
	char	*path = "log.txt";
	int		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	int	nb_piece = 0;

	t_info	*info;
	char	*line;
	int		i;
	int		x;
	int		y;
	int		t;

	// First ligne : exec shit
	get_next_line(0, &line);
	info = ft_new_info(((line[10] == '1') ? 'o' : 'x'));
	dprintf(fd, "LIGNE 1 : %s\n\n", line);

	if (get_next_line(0, &line))
		dprintf(fd, "> %s\n", line);

	// Get x_map and y_map
	ft_map_size(&info, line);
	//dprintf(fd, "Map (MaJ) : [%d|%d]\n", info->x_map, info->y_map);
	info->map = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	info->map_prev = ft_memalloc((sizeof(char *)) * (info->x_map + 1));
	(info->map)[info->x_map] = 0;
	(info->map_prev)[info->x_map] = 0;

	// Get map and map_prev
	get_next_line(0, &line);
	i = 0;
	while (i < info->x_map)
	{
		get_next_line(0, &line);
		(info->map)[i] = ft_strdup(ft_strsub(line, 4, info->x_map));
		(info->map_prev)[i] = ft_strdup(ft_strsub(line, 4, info->x_map));
		i++;
	}

	t = 0;
	while (1)
	{
		// Only from turn 2 : updates the map
		if (t++)
		{
			if (get_next_line(0, &line))
				dprintf(fd, "> %s\n", line);
			get_next_line(0, &line);
			i = 0;
			while (i < info->x_map)
			{
				get_next_line(0, &line);
				free((info->map)[i]);
				(info->map)[i] = ft_strdup(ft_strsub(line, 4, info->x_map));
				i++;
			}
		}
		if (debug)
			ft_display_map(info->map, fd);

		// Diff(map, map_prev) : spot new ennemies + updates map_prev
		if (info->map_prev)
		{
			x = 0;
			while ((info->map)[x])
			{	
				y = 0;
				while ((info->map)[x][y])
				{
					if ((info->map)[x][y] != (info->map_prev)[x][y])
					{
						//dprintf(fd, "	< A wild ennemi appears in [%d, %d] >\n", x, y);
						info->x_side = x;
						info->y_side = y;
						(info->map_prev)[x][y] = (info->map)[x][y];
					}
					y++;
				}
				x++;
			}
		}

		// Get x_piece
		get_next_line(0, &line);
		i = 0;
		while (line[i])
		{
			if (line[i] > '0' && line[i] < '9')
			{
				info->x_piece =	ft_atoi(line + i);
				while (line[i] > '0' && line[i] < '9')
					i++;
				info->y_piece =	ft_atoi(line + i);
				dprintf(fd, "Piece (Maj) : [%d|%d]\n", info->x_piece, info->y_piece);
				break ;
			}
			i++;
		}
		info->piece = ft_memalloc((sizeof(char *)) * (info->x_piece + 1));
		(info->piece)[info->x_piece] = 0;

		// Get piece
		i = 0;
		while (i < info->x_piece)
		{
			get_next_line(0, &line);
			(info->piece)[i] = ft_strdup(line);
			i++;
		}

		if (debug)
			ft_display_map(info->piece, fd);

		ft_get_place(info, fd);
		x = 0;
		y = 0;
		if (debug)
		{
			dprintf(fd, "%d %d\n", x, y);
			dprintf(fd, "nb_piece = %d\n", ++nb_piece);
		}
		//		dprintf(1, "%d %d\n", x, y);
	}
	return (0);
}
