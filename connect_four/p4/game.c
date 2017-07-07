#include "libft.h"
#include "p4.h"
#include <stdio.h>

void	display_game(int **plat)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
			printf("| %d |", plat[y][x]);
		printf("\n");
	}
}

int	**set_game(void)
{
	int	**plat;
	int	x;
	int	y;

	y = -1;
	plat = ft_memalloc(sizeof(int *) * 8);
	while (++y < 8)
	{
		plat[y] = ft_memalloc(sizeof(int) * 8);
		x = -1;
		while (++x < 8)
			plat[y][x] = 0;
	}
	return (plat);
}

t_puissance	*init_game(char	**av)
{
	t_puissance	*game;

	if (!(game = ft_memalloc(sizeof(t_puissance))))
		perror("");
	PLAT = set_game();
	P1 = ft_strdup(av[1]);
	P2 = ft_strdup(av[2]);
	P_X = 0;
	P_Y = 0;
	return (game);
}

/*
int	check_diago(t_puissance *game, int player, int x, int y)
{
	int	win = 1;

	while (PLAT[y - win][x - win] && (PLAT[y - win][x - win] == player))
	{
		win++;
		if (win == 4)
			return (4);
		if ((y - win < 0 && win != 4) || (x - win < 0 && win != 4))
			break ;
	}
	win = 1;
	while (PLAT[y - win][x + win] && (PLAT[y - win][x + win] == player))
	{
		win++;
		if (win == 4)
			return (4);
		if ((y - win < 0 && win != 4) || (x + win > 7 && win != 4))
			break ;
	}
	if (y < 7)
	{
		while (PLAT[y + win][x - win] && PLAT[y + win][x - win] == player)
		{
			win++;
			if (win == 4)
				return (4);
			if ((y + win > 7 && win != 4) || (x - win < 0 && win != 4))
				break ;
		}
	}
	if (y < 7)
	{
		while (PLAT[y + win][x + win] && PLAT[y + win][x + win] == player)
		{
			win++;
			if (win == 4)
				return (4);
			if ((y + win > 7 && win != 4) || (x + win > 7 && win != 4))
				break ; 
		}
	}
	return (0);
}

int	check_col(t_puissance *game, int player, int x, int y)
{
	int	win = 1;

	while (PLAT[y - win][x] && (PLAT[y - win][x] == player))
	{
		win++;
		if (y - win < 0 && win != 4)
			return (0);
		if (win == 4)
			return (4);
	}
	win = 1;
	if (y < 7)
	{
		while (PLAT[y + win][x] && (PLAT[y + win][x] == player))
		{
			win++;
			if (y + win > 7 && win != 4)
				return (0);
			if (win == 4)
				return (4);
		}
	}
	return (0);	
}

int	check_line(t_puissance *game, int player, int x, int y)
{
	int	win = 1;

	while (PLAT[y][x - win] && (PLAT[y][x - win] == player))
	{
		win++;
		if (win == 4)
			return (4);
		if (x - win < 0 && win != 4)
			break ;
	}
	win = 1;
	if (y < 7)
	{
		while (PLAT[y][x + win] && (PLAT[y][x + win] == player))
		{
			win++;
			if (win == 4)
				return (4);
			if (y + win > 7 && win != 4)
				break ;
		}
	}
	return (0);
}

int	check_win(t_puissance *game, int player, int x, int y)
{
	int	win = 1;

	win = check_line(game, player, x, y);
	if (win == 4)
		return (player);
	win = 1;
	win = check_col(game, player, x, y);
	if (win == 4)
		return (player);
	win = 1;
	win = check_diago(game, player, x, y);
	if (win == 4)
		return (player);
	return (0);	
}
*/

int	check_diago(t_puissance *game, int player)
{
	int	coef;

	coef = 0;
	printf("\nCOEF %d\n", coef);
	while ((PLAT[P_Y + coef][P_X + coef]) == player)
	{
		if (coef == 3)
		{
			printf("DIAGO POS [%d,%d]", P_X, P_Y);
			return (1);
		}
		coef++;
		printf("\nCOEF %d\n", coef);
		if (P_Y + coef > 7 || P_X + coef > 7)
			break ;
	}
	coef = 0;
	while ((PLAT[P_Y - coef][P_X - coef]) == player)
	{
		if (coef == 3)
		{
			printf("DIAGO NEG [%d,%d], %d", P_X, P_Y, player);
			return (1);
		}
		coef++;
		printf("\nCOEF %d\n", coef);
		if (P_Y - coef < 0 || P_X - coef < 0)
			break ;
	}
	coef = 0;
	while ((PLAT[P_Y + coef][P_X - coef]) == player)
	{
		if (coef == 3)
		{
			printf("DIAGO NEG line POS col [%d,%d], %d", P_X, P_Y, player);
			return (1);
		}
		coef++;
		printf("\nCOEF %d\n", coef);
		if (P_Y + coef > 7 || P_X - coef < 0)
			break ;
	}
	coef = 0;
	while ((PLAT[P_Y - coef][P_X + coef]) == player)
	{
		if (coef == 3)
		{
			printf("DIAGO NEG col POS line [%d,%d], %d", P_X, P_Y, player);
			return (1);
		}
		coef++;
		printf("\nCOEF %d\n", coef);
		if (P_Y - coef < 0 || P_X + coef > 7)
			break ;
	}
	return (0);
}

int	check_col(t_puissance *game, int player)
{
	int	coef;

	coef = 0;
	while ((PLAT[P_Y + coef][P_X]) == player)
	{
		if (coef == 3)
		{
			printf("COL POS [%d,%d]", P_X, P_Y);
			return (1);
		}
		coef++;
		if (P_Y + coef > 7)
			break ;
	}
	coef = 0;
	while ((PLAT[P_Y][P_X - coef]) == player)
	{
		if (coef == 3)
		{
			printf("COL NEG [%d,%d], %d", P_X, P_Y, player);
			return (1);
		}
		coef++;
		if (P_Y - coef < 0)
			break ;
	}
	return (0);
}

int	check_line(t_puissance *game, int player)
{
	int	coef;

	coef = 0;
	while (PLAT[P_Y][P_X + coef] == player)
	{
		if (coef == 3)
		{
			printf("LINE POS [%d,%d], %d", P_X, P_Y, player);
			return (1);
		}
		coef++;
		if (P_X + coef > 7)
			break ;
	}
	coef = 0;
	while (PLAT[P_Y][P_X - coef] == player)
	{
		if (coef == 3)
			return (1);
		coef++;
		if (P_X - coef < 0)
			break ;
	}
	return (0);
}

int	winner_is(t_puissance *game, int player)
{
	static int	turn = 0;
	int		r;

	r = 0;
	printf("\nTour %d\n", turn++);
	r = check_line(game, player);
	if (!r)
		r = check_col(game, player);
	if (!r)
		r =  check_diago(game, player);
	return (r);
}

void	process(t_puissance *game, int col_player, int player)
{
	int	y = 8;

	while (--y > -1)
	{	
		if (!PLAT[y][col_player - 1])
		{
			PLAT[y][col_player - 1] = player;
			P_X = col_player - 1;
			P_Y = y;
			printf("Placement en [colonne %d ligne %d]\n", col_player, y + 1);
			return ;
		}
	}
	printf("La colonne %d est full, dommage regarde mieux la prochaine fois\n", y);
}

int	main(int ac, char **av)
{
	t_puissance	*game;
	int		winner = 0;
	int		p1_col = 0;
	int		p2_col = 0;

	if (ac < 3 || ac > 3)
	{
		printf("Not enough players: Usage ./exe [name1] [name2]\n");
		return (1);
	}
	game = init_game(av);
	display_game(PLAT);
	while (!winner)
	{
		printf("%s (P1), entrez votre colonne (1 a 8) :\n", P1);
		scanf("%d", &p1_col);
		if (p1_col < 9 && p1_col > 0)
			process(game, p1_col, 1);
		winner = winner_is(game, 1);
		if (winner)
		{
			display_game(PLAT);
			printf("Le vainqueur de la partie est le joueur %s (P1)\n", P1);
			return (0);
		}
		display_game(PLAT);
		printf("%s (P2), entrez votre colonne (1 a 8) :\n", P2);
		scanf("%d", &p2_col);
		if (p2_col < 9 && p2_col > 0)
			process(game, p2_col, 2);	
		winner = winner_is(game, 2);
		if (winner)
		{
			display_game(PLAT);
			printf("Le vainqueur de la partie est le joueur %s (P2)\n", P2);
			return (0);
		}
		display_game(PLAT);
	}
	return (0);
}
