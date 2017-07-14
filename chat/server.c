/****************** SERVER CODE ****************/

#include "chat.h"
#include "libft.h"

void		connected(int socket, t_lsocket *list_socket)
{
	char	buffer[1024];
	int	r;
	t_lsocket	*current;

	printf("CONNECTED FUN\n");
	current = list_socket;
	while (1)
	{
		if ((r = recv(socket, buffer, 1024, 0)) < 1)
			perror("");
		printf("RECV\n");
		while (current)
		{
			printf("ID SOCKET %d\n", current->socket);
			if (current->socket != socket)
				send(current->socket, buffer, strlen(buffer), 0);
			current = current->next;
		}
		printf("OUT LIST SOCKET\n");
	}
}

t_lsocket	*create_socket(int socket, t_lsocket *list_socket)
{
	t_lsocket	*new_sock;

	new_sock = ft_memalloc(sizeof(t_lsocket));
	new_sock->socket = socket;
	if (!(new_sock->pid = fork()))
		connected(socket, list_socket);
	new_sock->next = NULL;
	return (new_sock);
}

void	add_socket(t_lsocket *list_socket, t_lsocket *socket)
{
	socket->next = list_socket;	
	list_socket = socket;
}

int	check_name(char *name, t_lsocket *list_socket)
{
	(void)name;
	(void)list_socket;
	return (1);
}

int 	main(int ac, char **av)
{
	int 		server_socket;
	int		connect_socket;
	int		new_pid;
	t_lsocket	*new_socket;
	t_lsocket	*list_socket;
	char 		buffer[1024];
	t_sock		serverAddr;
	t_sock		serverStorage;
	socklen_t	addr_size;
	ssize_t		r;
	int		op_val = 1;

	printf("| SERVER |\n");

	(void)av;
	if (!ac)
		return (0);

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(0);
	}

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &op_val, sizeof(int)) < 0)
		perror("setsockopt");

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	/* Set port number, using htons function to use proper byte order */
	/* Set IP address to localhost */
	/* Set all bits of the padding field to 0 */
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);;
	//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*---- Bind the address struct to the socket ----*/
	if (bind(server_socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)))
	{
		perror("bind");
		exit(0);
	}

	addr_size = sizeof serverStorage;

	while (1)
	{
		/*---- Listen on the socket, with 5 max connection requests queued ----*/
		listen(server_socket,5);
		/*---- Accept call creates a new socket for the incoming connection ----*/
		if ((connect_socket = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size)) < 0)
			perror("");
		printf("Connection\n");
		if ((r = recv(connect_socket, buffer, 1024, 0)) < 1)
			perror("");
		if (check_name(buffer, list_socket))
		{
			send(connect_socket, buffer, strlen(buffer), 0);
			new_socket = create_socket(connect_socket, list_socket);
			if (!list_socket)
				list_socket = new_socket;
			else
				add_socket(list_socket, new_socket);
		}
		else
		{
			buffer[0] = '\0';
			send(connect_socket, buffer, strlen(buffer), 0);
		}
		/*
		while (list_socket)
		{
			if ((r = recv(list_socket->socket, buffer, 1024, 0)) < 1)
				perror("");
			close(list_socket->socket);
			printf("Socket closed\n");
		}
		*/
	}
	return 0;
}
