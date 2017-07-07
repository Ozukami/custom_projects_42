/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 03:37:00 by apoisson          #+#    #+#             */
/*   Updated: 2017/05/20 04:21:12 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_my_printf(char *format, ...)
{
	va_list	ap;
	char	*to_print;
	int		i;

	va_start(ap, format);
	to_print = ft_strdup("");
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
				to_print = ft_strjoinf_l(to_print, "%");
			else if (format[i + 1] == 'd')
				to_print = ft_strjoinf(to_print, ft_itoa(va_arg(ap, int)));
			else if (format[i + 1] == 's')
				to_print = ft_strjoinf_l(to_print, va_arg(ap, char *));
			i++;
		}
		else
			to_print = ft_strjoinf(to_print, ft_strsub(format, i, 1));
	}
	va_end(ap);
	ft_putstr(to_print);
	ft_strdel(&to_print);
}
