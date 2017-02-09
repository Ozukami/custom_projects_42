/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_tracking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 10:40:40 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/29 10:40:58 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_subtrack(int *i, t_tetri *tetri, int *k, int len)
{
	int		j;

	while ((tetri->tetri)[*k] < 'A' || (tetri->tetri)[*k] > 'Z')
	{
		while ((tetri->tetri)[*k] == '.')
		{
			*k += 1;
			*i += 1;
		}
		if ((tetri->tetri)[*k] == '\n')
		{
			if ((tetri->tetri)[(*k) + 1] == '\0')
				return (1);
			j = 0;
			while ((tetri->tetri)[j] != '\n')
				j++;
			*k += 1;
			*i = *i + len - j;
		}
		if (*i >= len * len)
			return (0);
	}
	return (2);
}

int		ft_place_tracking(char ***tab, int i, t_tetri *tetri, int k)
{
	int		len;
	int		r;

	len = ft_strlen(tab[0][0]);
	if (k > 0)
		if (i % len == 0 && (tetri->tetri)[k - 1] != '\n'
				&& (tetri->tetri)[k] != '\n')
			return (0);
	r = ft_subtrack(&i, tetri, &k, len);
	if (r == 0)
		return (0);
	else if (r == 1)
		return (1);
	if (tab[0][i / len][i % len] == '.')
	{
		tab[0][i / len][i % len] = (tetri->tetri)[k];
		if (ft_place_tracking(tab, i + 1, tetri, k + 1))
			return (1);
		tab[0][i / len][i % len] = '.';
	}
	return (0);
}

void	ft_delete_tetri(char ***tab, t_tetri *tetri)
{
	int		i;
	int		j;

	i = 0;
	while (tab[0][i])
	{
		j = 0;
		while (tab[0][i][j])
		{
			if (tab[0][i][j] == tetri->l)
				tab[0][i][j] = '.';
			j++;
		}
		i++;
	}
}

int		ft_place(char ***tab, t_tetri *tetrilist, size_t opti_size)
{
	int		len;

	len = ft_strlen(tab[0][0]);
	while (tetrilist)
	{
		while (tetrilist->i < (int)(opti_size * opti_size))
		{
			if (ft_place_tracking(tab, (tetrilist->i)++, tetrilist, 0))
				break ;
			if (tetrilist->i == (int)(opti_size * opti_size))
			{
				tetrilist->i = 0;
				if (tetrilist->prev)
				{
					tetrilist = tetrilist->prev;
					ft_delete_tetri(tab, tetrilist);
				}
				else
					return (0);
			}
		}
		tetrilist = tetrilist->next;
	}
	return (1);
}
