/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_epur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 08:18:35 by apoisson          #+#    #+#             */
/*   Updated: 2017/06/12 04:10:46 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*str_epur(char *str)
{
	char	*epur;
	char	**split;
	int		i;

	if (!(split = ft_strsplit_whitespaces((const char *)str, ' ', '\t')))
	{
		ft_strdel(&str);
		return (NULL);
	}
	if (!split[0])
	{
		ft_strdel(&str);
		free_map(split);
		return (NULL);
	}
	epur = ft_strdup(split[0]);
	i = 0;
	while (split[++i])
	{
		epur = ft_straddchar(epur, ' ');
		epur = ft_strjoinf_l(epur, split[i]);
	}
	free_map(split);
	ft_strdel(&str);
	return (epur);
}
