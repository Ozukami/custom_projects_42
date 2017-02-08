/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 08:58:34 by apoisson          #+#    #+#             */
/*   Updated: 2016/12/15 09:01:21 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(char *s, char c)
{
	char		*stack;
	int			i;

	if (!(stack = ft_memalloc(ft_strlen(s) + 2)))
		return (NULL);
	i = -1;
	while (s[++i])
		stack[i] = s[i];
	stack[i] = c;
	free(s);
	return (stack);
}
