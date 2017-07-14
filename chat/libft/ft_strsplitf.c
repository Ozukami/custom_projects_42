/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:54:26 by apoisson          #+#    #+#             */
/*   Updated: 2017/06/12 04:30:50 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static char	*ft_add_word_tab(char *s, char c, int *i)
{
	int		j;
	char	*str;

	j = *i;
	while (s[*i] && s[*i] != c)
		*i = *i + 1;
	str = ft_strsub(s, j, *i - j);
	while (s[*i] && s[*i] == c)
		*i = *i + 1;
	return (str);
}

char		**ft_strsplitf(char *s, char c)
{
	int			i;
	int			j;
	int			word;
	char		**tab;

	i = 0;
	j = 0;
	if (!s || !c)
		return (NULL);
	word = ft_count_word(s, c);
	if (!(tab = ft_memalloc(sizeof(tab) * (word + 1))))
		return (NULL);
	while (s[i] == c)
		i++;
	while (j < word && s[i])
	{
		tab[j] = ft_add_word_tab(s, c, &i);
		j++;
	}
	tab[j] = 0;
	ft_strdel(&s);
	return (tab);
}
