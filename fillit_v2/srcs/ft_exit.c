/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:02:56 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/27 12:52:42 by qumaujea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_usage(void)
{
	ft_putendl("usage: ./fillit file");
	exit(0);
}

void	ft_error(void)
{
	ft_putendl("error");
	exit(0);
}

void	ft_tafritatoukompri(char ***tab)
{
	int	i;

	i = 0;
	while (tab[0][i])
	{
		free(tab[0][i]);
		i++;
	}
	free(tab[0]);
	tab = NULL;
}
