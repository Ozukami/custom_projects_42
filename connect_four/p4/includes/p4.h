#ifndef P4_H
# define P4_H

# define	PLAT		(game->game_plat)
# define	P1		(game->name_p1)
# define	P2		(game->name_p2)
# define	P_X		(game->pos_x)
# define	P_Y		(game->pos_y)
# define	LAST_PLAY	PLAT[P_Y][P_X]

typedef struct	s_puissance	t_puissance;

struct		s_puissance
{
	int	**game_plat;
	char	*name_p1;
	char	*name_p2;
	int	pos_x;
	int	pos_y;
};

#endif
