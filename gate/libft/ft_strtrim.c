/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 07:15:55 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/16 12:54:21 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*trim;
	size_t	strtspc;
	size_t	endspc;
	size_t	i;

	if (!s)
		return (NULL);
	strtspc = 0;
	while (s[strtspc] && ft_check_spaces(s[strtspc]))
		strtspc++;
	if (strtspc == ft_strlen(s))
		return (ft_strdup("\0"));
	endspc = 0;
	while (ft_check_spaces(s[ft_strlen(s) - endspc - 1]))
		endspc++;
	if (!(trim = (char *)ft_memalloc(ft_strlen(s) - (strtspc + endspc) + 1)))
		return (NULL);
	i = 0;
	while (i + strtspc < ft_strlen(s) - endspc)
	{
		trim[i] = s[i + strtspc];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
