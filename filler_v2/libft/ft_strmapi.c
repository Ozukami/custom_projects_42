/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 05:09:20 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/16 11:48:52 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rep;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	if (!(rep = (char *)ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		rep[i] = f(i, s[i]);
		i++;
	}
	rep[ft_strlen(s)] = '\0';
	return (rep);
}
