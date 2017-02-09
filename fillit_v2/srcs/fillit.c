/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:01:47 by apoisson          #+#    #+#             */
/*   Updated: 2016/11/19 15:08:57 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		ft_usage();
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_error();
	ft_process(fd);
	if (close(fd) == -1)
		ft_error();
	return (0);
}
