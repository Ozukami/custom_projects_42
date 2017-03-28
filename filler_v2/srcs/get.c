/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:11:40 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/28 23:35:27 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_get_piece_size(t_info *info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			PIECE_X = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			PIECE_Y = ft_atoi(line + i);
			break ;
		}
		i++;
	}
	if (info->t > 1)
		free_map(PIECE);
	free(PIECE);
	PIECE = ft_memalloc((sizeof(char *)) * (PIECE_X + 1));
	PIECE[PIECE_X] = 0;
}

void		ft_get_piece(t_info *info)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (i < PIECE_X)
	{
		get_next_line(0, &line);
		PIECE[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
}

void		ft_get_map_size(t_info *info)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			MAP_X = ft_atoi(line + i);
			while (line[i] >= '0' && line[i] <= '9')
				i++;
			MAP_Y = ft_atoi(line + i);
			ft_strdel(&line);
			return ;
		}
		i++;
	}
	ft_strdel(&line);
}

void		ft_get_map(t_info *info, int t)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < MAP_X)
	{
		get_next_line(0, &line);
		if (!t)
			MAP_PREV[i] = ft_strsub(line, 4, MAP_Y);
		else
			ft_strdel(&(MAP[i]));
		MAP[i] = ft_strsub(line, 4, MAP_Y);
		ft_strdel(&line);
		i++;
	}
}

int			ft_update_map(t_data *data)
{
	char	*line;

	line = NULL;
	if ((INFO->t)++)
	{
		ft_skip_n_line(2);
		ft_get_map(INFO, INFO->t);
		ft_wild_ennemy_appears(data);
	}
	get_next_line(0, &line);
	ft_get_piece_size(INFO, line);
	ft_strdel(&line);
	ft_get_piece(INFO);
	return (1);
}
