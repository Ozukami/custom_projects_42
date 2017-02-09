/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 23:22:39 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 03:36:30 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_color		*ft_new_color(int color, char *name)
{
	t_color		*new;

	new = ft_memalloc(sizeof(t_color));
	new->color = color;
	new->name = name;
	return (new);
}

t_color		**ft_init_colors(void)
{
	t_color		**new;

	new = ft_memalloc(sizeof(t_color) * 29);
	new[0] = ft_new_color(0x00000000, "black");
	new[1] = ft_new_color(0x00FFFFFF, "white");
	new[2] = ft_new_color(0x00FF0000, "red");
	new[3] = ft_new_color(0x000000FF, "blue");
	new[4] = ft_new_color(0x0000FF00, "green");
	new[5] = ft_new_color(0x00FFFF00, "yellow");
	new[6] = ft_new_color(0x00FF8000, "orange");
	new[7] = ft_new_color(0x00a020f0, "purple");
	new[8] = ft_new_color(0x0000ffff, "cyan");
	new[9] = ft_new_color(0x00ff00ff, "magenta");
	new[10] = ft_new_color(0x008b4513, "brown");
	new[11] = ft_new_color(0x00666666, "grey");
	new[12] = ft_new_color(0x00ff69b4, "pink");
	new[13] = ft_new_color(0x0000bfff, "sky_blue");
	new[14] = ft_new_color(0x00228b22, "forest_green");
	new[15] = ft_new_color(0x008b0000, "dark_red");
	new[16] = ft_new_color(0x00ffd700, "gold");
	new[17] = ft_new_color(0x00bfbfbf, "light_grey");
	new[18] = ft_new_color(0x003b3b3b, "dark_grey");
	new[19] = ft_new_color(0x00104e8b, "dark_blue");
	new[20] = ft_new_color(0x0000ced1, "turquoise");
	new[21] = ft_new_color(0x00008b8b, "dark_cyan");
	new[22] = ft_new_color(0x00ee1289, "dark_pink");
	new[23] = ft_new_color(0x00fa8072, "salmon");
	new[24] = ft_new_color(0x00e066ff, "light_purple");
	new[25] = ft_new_color(0x00551a8b, "dark_purple");
	new[26] = ft_new_color(0x00ffdab9, "beige");
	new[27] = ft_new_color(0x0098fb98, "light_green");
	new[28] = NULL;
	return (new);
}

int		ft_pick_color(t_color **colors, char c)
{
	if (c >= 'A' && c <= 'Z')
		return ((colors[c - 'A' + 2])->color);
	return (0x00000000);
}

int		ft_get_color(t_color **colors, char *name)
{
	int		i;

	i = 0;
	while (colors[i])
	{
		if (ft_strequ((colors[i])->name, name))
			return ((colors[i])->color);
		i++;
	}
	return (0x00000000);
}

int		ft_draw_line(void *mlx, void *win, int x, int y,
		int value, int dir, int color)
{
	int	i;

	i = 0;
	while (i < value)
	{
		if (!dir)
			y++;
		if (dir == 1)
			x++;
		if (dir == 2)
			y--;
		if (dir == 3)
			x--;
		if (!mlx_pixel_put(mlx, win, x, y, color))
			return (0);
		i++;
	}
	return (1);
}

void	ft_draw_square(void *mlx, void *win, int x, int y, int size, int color)
{
	if (!ft_draw_line(mlx, win, x, y, size, 1, color))
		printf("Error\n");
	if (!ft_draw_line(mlx, win, x, y, size, 0, color))
		printf("Error\n");
	if (!ft_draw_line(mlx, win, x, y + size, size, 1, color))
		printf("Error\n");
	if (!ft_draw_line(mlx, win, x + size, y, size, 0, color))
		printf("Error\n");
}

void	ft_fill_square(void *mlx, void *win, int x, int y, int size, int color)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (!ft_draw_line(mlx, win, x, y + i, size, 1, color))
			printf("Error\n");
		i++;
	}
}

int	ft_key_event(int key)
{
	if (key == 53 || key == 49)
	{
		printf("Key (%d) -> Exit!\n", key);
		exit(0);
	}
	else
		printf("Key (%d)\n", key);
	return (1);
}

int	ft_mouse_event(int button, int x, int y)
{
	printf("Mouse (%d) at [%d,%d]\n", button, x, y);
	return (1);
}

void	ft_display_tab(char **tab)
{
	t_color	**colors;
	void		*mlx;
	void		*win;
	int			size;
	int			loop;
	int			x;
	int			y;
	char		c;

	colors = ft_init_colors();
	size = 0;
	while (tab[size])
		size++;
	mlx = mlx_init();
	win = mlx_new_window(mlx, (size * 25) + 21,
			(size * 25) + 21, "Fillit");
	if (!mlx_key_hook(win, &ft_key_event, 0))
	{
		printf("Error\n");
		exit(0);
	}
	if (!mlx_mouse_hook(win, &ft_mouse_event, 0))
	{
		printf("Error\n");
		exit(0);
	}
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			c = tab[y][x];
			ft_draw_square(mlx, win, (x * 25) + 10, (y * 25) + 10,
					25, ft_get_color(colors, "white"));
			ft_fill_square(mlx, win, (x * 25) + 11, (y * 25) + 11,
					23, ft_pick_color(colors, c));
//			mlx_string_put(mlx, win, (x * 25) + 17, (y * 25) + 12,
//					0x00FFFFFF, &c);
			x++;
		}
		y++;
	}
	loop = mlx_loop(mlx);
}
