/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 11:26:31 by qumaujea          #+#    #+#             */
/*   Updated: 2016/11/27 12:25:28 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_bpoint(char *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n - 1)
	{
		s[i] = '.';
		i++;
	}
	s[i] = 0;
}

char	*ft_fillalloc(size_t size)
{
	char	*rep;

	rep = malloc(size);
	if (rep)
	{
		ft_bpoint(rep, size);
		return (rep);
	}
	return (NULL);
}

char	**ft_init(size_t len)
{
	char	**tab;
	size_t	i;

	i = 0;
	if (!(tab = malloc((sizeof(char *)) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (!(tab[i] = ft_fillalloc((sizeof(char)) * (len + 1))))
			return (NULL);
		i++;
	}
	tab[len] = 0;
	return (tab);
}
