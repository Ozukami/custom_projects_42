/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:16:40 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/08 23:21:30 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_process_2(t_tetri *tetrilist)
{
	char	**tab;
	int		i;
	size_t	opti_size;
	int		z;

	i = 0;
	while (!(opti_size = ft_sqrt(ft_tetrilen(tetrilist) * 4 + i)))
		i++;
	opti_size--;
	tab = ft_init(opti_size);
	while (!ft_place(&tab, tetrilist, opti_size))
	{
		ft_tafritatoukompri(&tab);
		opti_size++;
		tab = ft_init(opti_size);
	}
	z = 0;
	while (tab[z])
	{
		ft_putendl(tab[z]);
		z++;
	}
	ft_display_tab(tab);
	ft_tafritatoukompri(&tab);
}

void	ft_process_3(t_tetri *tetrilist)
{
	ft_tetriter(&tetrilist, &ft_tetri_format);
	ft_tetrirev(&tetrilist);
	ft_process_2(tetrilist);
}

void	ft_process(int fd)
{
	t_tetri	*tetrilist;
	char	buf[BUFSIZE + 1];
	char	l;
	int		r;
	int		empty;

	l = 'A';
	tetrilist = NULL;
	empty = 1;
	while ((r = read(fd, buf, BUFSIZE)))
	{
		empty = 0;
		if (r < 20 || l > 'Z')
			ft_error();
		buf[r] = '\0';
		if (!ft_verif(buf))
			ft_error();
		ft_tetriadd(&tetrilist, ft_tetrinew(ft_str_replace(buf, l), l));
		l++;
	}
	if (empty == 1)
		ft_error();
	if (ft_strlen(tetrilist->tetri) != 20)
		ft_error();
	ft_process_3(tetrilist);
}
