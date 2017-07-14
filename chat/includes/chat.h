/****************** SERVER CODE ****************/

#ifndef PFC_H

# define PFC_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>

typedef struct sockaddr_in	t_sock;
typedef struct s_lsocket	t_lsocket;

# define IP_ADDR	"127.0.0.1"

struct	s_lsocket
{
	int	pid;
	int	socket;
	t_lsocket	*next;
};

#endif
