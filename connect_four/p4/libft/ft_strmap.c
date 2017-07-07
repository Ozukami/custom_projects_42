/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 04:39:05 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/16 11:48:26 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*rep;
	int		i;

	if (!s || !f)
		return (NULL);
	if (!(rep = (char *)ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		rep[i] = f(s[i]);
		i++;
	}
	rep[ft_strlen(s)] = '\0';
	return (rep);
}
