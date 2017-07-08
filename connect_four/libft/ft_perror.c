/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 04:46:57 by apoisson          #+#    #+#             */
/*   Updated: 2017/06/15 00:22:54 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *error)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putendl_fd(error, 2);
	exit(0);
}
