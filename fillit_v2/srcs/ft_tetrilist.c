/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tetrilist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 14:58:58 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/29 10:27:14 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri	*ft_tetrinew(char *tetri, char l)
{
	t_tetri	*tetrinew;

	if (!(tetrinew = malloc(sizeof(t_tetri))))
		return (NULL);
	if (tetri == NULL)
		tetrinew->tetri = NULL;
	else
	{
		tetrinew->tetri = malloc(BUFSIZE + 1);
		ft_memcpy(tetrinew->tetri, tetri, BUFSIZE + 1);
	}
	tetrinew->next = NULL;
	tetrinew->prev = NULL;
	tetrinew->l = l;
	tetrinew->i = 0;
	return (tetrinew);
}

void	ft_tetriadd(t_tetri **begin, t_tetri *new)
{
	new->next = *begin;
	new->prev = NULL;
	*begin = new;
}

void	ft_tetrirev(t_tetri **begin)
{
	t_tetri	*current;
	t_tetri	*tmp1;
	t_tetri	*tmp2;

	current = *begin;
	tmp1 = NULL;
	tmp2 = NULL;
	while (current)
	{
		tmp1 = current;
		current = current->next;
		tmp1->next = tmp2;
		tmp1->prev = current;
		tmp2 = tmp1;
	}
	*begin = tmp1;
}

size_t	ft_tetrilen(t_tetri *tetrilist)
{
	size_t	i;

	i = 1;
	while (tetrilist->next)
	{
		tetrilist = tetrilist->next;
		i++;
	}
	return (i);
}

void	ft_tetriter(t_tetri **begin, char *(*f)(char *s))
{
	t_tetri	*current;

	current = *begin;
	while (current)
	{
		current->tetri = f(current->tetri);
		current = current->next;
	}
}
