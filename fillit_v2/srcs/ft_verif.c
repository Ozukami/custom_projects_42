/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 17:46:19 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/22 08:07:34 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Verifie le fichier et retourne 1 si il est valide
*/

int		ft_verif(char *s)
{
	return (ft_verif_1(s) && ft_verif_2(s, -1, -1, -1));
}

/*
** Verifie si le fichier est bien formate
*/

int		ft_verif_1(char *s)
{
	int		i;
	int		bloc;

	i = 0;
	bloc = 0;
	if (ft_strlen(s) == 21 && s[20] != '\n')
		return (0);
	while (s[i])
	{
		if (i % 5 == 4 && s[i] != '\n')
			return (0);
		if (s[i] != '#' && s[i] != '.' && s[i] != '\n')
			return (0);
		if (s[i] == '#')
			bloc++;
		i++;
	}
	if (bloc != 4)
		return (0);
	return (1);
}

/*
** Recupere les indices des 4 '#' pour verifier si le tetrimino est valide
*/

int		ft_verif_2(char *s, int a, int b, int c)
{
	int		i;
	int		d;

	i = 0;
	d = -1;
	while (s[i])
	{
		if (s[i] == '#')
		{
			if (a == -1)
				a = i;
			else if (b == -1)
				b = i;
			else if (c == -1)
				c = i;
			else if (d == -1)
				d = i;
		}
		i++;
	}
	return (ft_verif_3(a, b, c, d));
}

/*
** Retourne 1 si les 4 '#' sont bien cote a cote
** Lors de l'appel de ft_check_2, on sait que les '#' sont au moins
** groupes 2 par 2
*/

int		ft_verif_3(int a, int b, int c, int d)
{
	if (ft_check_1(a, b) && ft_check_1(a, c) && ft_check_1(a, d))
		return (0);
	if (ft_check_1(b, a) && ft_check_1(b, c) && ft_check_1(b, d))
		return (0);
	if (ft_check_1(c, a) && ft_check_1(c, b) && ft_check_1(c, d))
		return (0);
	if (ft_check_1(d, a) && ft_check_1(d, b) && ft_check_1(d, c))
		return (0);
	return (ft_check_2(a, b, c, d));
}
