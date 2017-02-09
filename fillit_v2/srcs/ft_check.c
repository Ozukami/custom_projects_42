/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 07:56:26 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/22 08:09:28 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Retourne 1 si a et b ne sont pas voisins
*/

int		ft_check_1(int a, int b)
{
	if (a != b - 1 && a != b - 5 && a != b + 1 && a != b + 5)
		return (1);
	return (0);
}

/*
** Verifie si un des '#' a au moins 2 voisins, on sait alors
** que les 2 groupes de 2 '#' sont forcement colles0
*/

int		ft_check_2(int a, int b, int c, int d)
{
	if (!((ft_check_1(a, b) && ft_check_1(a, c))
			|| (ft_check_1(a, b) && ft_check_1(a, d))
			|| (ft_check_1(a, c) && ft_check_1(a, d))))
		return (1);
	if (!((ft_check_1(b, a) && ft_check_1(b, c))
			|| (ft_check_1(b, a) && ft_check_1(b, d))
			|| (ft_check_1(b, c) && ft_check_1(b, d))))
		return (1);
	if (!((ft_check_1(c, a) && ft_check_1(c, b))
			|| (ft_check_1(c, a) && ft_check_1(c, d))
			|| (ft_check_1(c, b) && ft_check_1(c, d))))
		return (1);
	if (!((ft_check_1(d, a) && ft_check_1(d, b))
			|| (ft_check_1(d, a) && ft_check_1(d, c))
			|| (ft_check_1(d, b) && ft_check_1(d, c))))
		return (1);
	return (0);
}
