
#ifndef CONNECT_FOUR_H
# define CONNECT_FOUR_H

# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>

# define DEFAULT		"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"

# define IP_ADDR		"10.13.12.19"
# define BUF_SIZE		1024
# define PSEUDO_SIZE	128

# define TRAY			(game->tray)
# define P1				(game->p1)
# define P2				(game->p2)

# define P1_PSEUDO		((game->p1)->pseudo)
# define P1_SOCKET		((game->p1)->socket)
# define P1_ID			((game->p1)->id)
# define P2_PSEUDO		((game->p2)->pseudo)
# define P2_SOCKET		((game->p1)->socket)
# define P2_ID			((game->p2)->id)

typedef struct sockaddr_in	t_sock;
typedef struct s_game		t_game;
typedef struct s_player		t_player;

struct s_game
{
	int			**tray;
	t_player	*p1;
	t_player	*p2;
};

struct s_player
{
	int			id;
	char		*pseudo;
	int			is_host;
	int			socket;
};

#endif
