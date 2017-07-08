/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:45:38 by apoisson          #+#    #+#             */
/*   Updated: 2017/06/09 10:04:56 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s, char c1, char c2)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c1 && (s[i + 1] == c1))
				|| (s[i] != c2 && (s[i + 1] == c2))
				|| s[i + 1] == '\0')
			word++;
		i++;
	}
	return (word);
}

static char	*ft_add_word_tab(const char *s, char c1, char c2, int *i)
{
	int		j;
	char	*str;

	j = *i;
	while (s[*i] && (s[*i] != c1 && s[*i] != c2))
		*i = *i + 1;
	str = ft_strsub(s, j, *i - j);
	while (s[*i] && (s[*i] == c1 || s[*i] == c2))
		*i = *i + 1;
	return (str);
}

char		**ft_strsplit_whitespaces(char const *s, char c1, char c2)
{
	int			i;
	int			j;
	int			word;
	char		**tab;

	i = 0;
	j = 0;
	if (!s || !c1 || !c2)
		return (NULL);
	word = ft_count_word(s, c1, c2);
	if (!(tab = ft_memalloc(sizeof(tab) * (word + 1))))
		return (NULL);
	while (s[i] == c1 || s[i] == c2)
		i++;
	while (j < word && s[i])
	{
		tab[j] = ft_add_word_tab(s, c1, c2, &i);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
