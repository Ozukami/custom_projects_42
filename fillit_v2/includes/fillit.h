/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 14:12:43 by apoisson          #+#    #+#             */
/*   Updated: 2017/02/09 01:19:26 by apoisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# define BUFSIZE 21

/*
** Liste contenant les tetriminos
*/

typedef struct		s_tetri
{
	struct s_tetri	*next;
	struct s_tetri	*prev;
	char			*tetri;
	char			l;
	int				i;
}					t_tetri;

typedef struct		s_color
{
	int				color;
	char			*name;
}					t_color;

t_color				**ft_init_colors(void);
t_color				*ft_init_color(int color, char *name);

/*
** Fonctions generales
*/

void				ft_usage(void);
void				ft_error(void);
void				ft_tafritatoukompri(char ***tab);
void				ft_process(int fd);
char				**ft_init(size_t len);

/*
** Back tracking
*/

int					ft_subtrack(int *i, t_tetri *tetri, int *k, int len);
int					ft_place_tracking(char ***tab, int i, t_tetri *tetri,
		int k);
void				ft_delete_tetri(char ***tab, t_tetri *tetri);
int					ft_place(char ***tab, t_tetri *tetrilist, size_t opti_size);

/*
** Fonctions permettant de formater les tetri
*/

char				*ft_tetri_format(char *s);
char				*ft_str_replace(char *s, char c);

/*
** Fonctions permettant de verifier le fichier
*/

int					ft_verif(char *s);
int					ft_verif_1(char *s);
int					ft_verif_2(char *s, int a, int b, int c);
int					ft_verif_3(int a, int b, int c, int d);
int					ft_check_1(int a, int b);
int					ft_check_2(int a, int b, int c, int d);

/*
** Fonctions permettant de manipuler la liste de tetriminos
*/

t_tetri				*ft_tetrinew(char *tetri, char l);
void				ft_tetriadd(t_tetri **begin, t_tetri *new);
void				ft_tetrirev(t_tetri **begin);
size_t				ft_tetrilen(t_tetri *tetrilist);
void				ft_tetriter(t_tetri **begin, char *(*f)(char *s));

/*
** MLX Functions
*/

void				ft_display_tab(char **tab);

#endif
