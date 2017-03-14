/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 08:35:46 by apoisson          #+#    #+#             */
/*   Updated: 2017/03/14 00:48:49 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char *s1, char *s2)
{
	char		*stack;
	int			i;
	int			j;

	if (!(stack = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		ft_putstr("[ERROR MALLOC] > ft_strjoinf\n");
		return (NULL);
	}
	i = -1;
	j = -1;
	while (s1[++i])
		stack[i] = s1[i];
	while (s2[++j])
		stack[i + j] = s2[j];
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (stack);
}
