/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumaujea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 11:38:11 by qumaujea          #+#    #+#             */
/*   Updated: 2016/11/29 10:24:59 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_format_end(char **s)
{
	int		i;

	i = 0;
	while (s[0][i])
	{
		if (s[0][i + 1])
			if (s[0][i] == '\n' && s[0][i + 1] == '\n')
				s[0][i + 1] = '\0';
		i++;
	}
}

void	ft_format_line(char **s)
{
	int		i;

	ft_format_end(s);
	i = 0;
	while (i < 16)
	{
		if ((s[0][i] == '.' || s[0][i] == 'x')
				&& (s[0][i + 1] == '.' || s[0][i + 1] == 'x')
				&& (s[0][i + 2] == '.' || s[0][i + 2] == 'x')
				&& (s[0][i + 3] == '.' || s[0][i + 3] == 'x'))
		{
			s[0][i] = 'x';
			s[0][i + 1] = 'x';
			s[0][i + 2] = 'x';
			s[0][i + 3] = 'x';
			s[0][i + 4] = 'x';
		}
		i = i + 5;
	}
}

void	ft_format_col(char **s)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if ((s[0][i] == '.' || s[0][i] == 'x')
				&& (s[0][i + 5] == '.' || s[0][i + 5] == 'x')
				&& (s[0][i + 10] == '.' || s[0][i + 10] == 'x')
				&& (s[0][i + 15] == '.' || s[0][i + 15] == 'x'))
		{
			s[0][i] = 'x';
			s[0][i + 5] = 'x';
			s[0][i + 10] = 'x';
			s[0][i + 15] = 'x';
		}
		i++;
	}
}

char	*ft_tetri_format(char *s)
{
	int		i;
	int		j;
	size_t	len;
	char	*rep;

	ft_format_line(&s);
	ft_format_col(&s);
	len = ft_strlen(s);
	i = -1;
	while (s[++i])
		if (s[i] == 'x')
			len--;
	if (!(rep = ft_memalloc(len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == 'x')
			i++;
		rep[j] = s[i];
		i++;
		j++;
	}
	return (rep);
}

char	*ft_str_replace(char *s, char c)
{
	int		i;
	char	*rep;

	if (!(rep = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '#')
			rep[i] = c;
		else
			rep[i] = s[i];
		i++;
	}
	return (rep);
}
