/****************** SERVER CODE ****************/

#include "pfc.h"

char	*get_move(int i)
{
	if (i == 1)
		return ("Rock");
	if (i == 2)
		return ("Paper");
	return ("Scissors");
}

int 	main(int ac, char **av)
{
	int 		server_socket, p1_socket, p2_socket;
	char 		buffer[1024];
	t_sock		serverAddr;
	t_sock		serverStorage;
	socklen_t	addr_size;
	ssize_t		r;
	int			op_val = 1;
	char		*p1_move;
	char		*p2_move;

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
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
		if(listen(server_socket,5)==0)
			printf("Listening...\n");
		else
			printf("Error\n");

		/*---- Accept call creates a new socket for the incoming connection ----*/
		if ((p1_socket = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size)) < 0)
			perror("");

		printf("Connection accepted (P1)\n");

		if ((r = recv(p1_socket, buffer, 1024, 0)) == -1)
			perror("");
		buffer[r] = '\0';
		printf("Player name = %s\n", buffer);

		/*---- Listen on the socket, with 5 max connection requests queued ----*/
		if(listen(server_socket,5)==0)
			printf("Listening...\n");
		else
			printf("Error\n");

		/*---- Accept call creates a new socket for the incoming connection ----*/
		if ((p2_socket = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size)) < 0)
			perror("");

		printf("Connection accepted (P2)\n");

		if ((r = recv(p2_socket, buffer, 1024, 0)) == -1)
			perror("");
		buffer[r] = '\0';
		printf("Player name = %s\n", buffer);

		sprintf(buffer, " -- NEW GAME --\n");
		send(p1_socket, buffer, strlen(buffer), 0);
		sprintf(buffer, " -- NEW GAME --\n");
		send(p2_socket, buffer, strlen(buffer), 0);

		int		turn = 0;
		int		loop = 1;
		p1_move = malloc(1024);
		p2_move = malloc(1024);
		printf("Waiting for players...\n");
		while (loop)
		{
			printf("Turn : %d\n", turn++);
			printf("Waiting for P1...\n");

			if ((r = recv(p1_socket, p1_move, 1024, 0)) < 1)
			{
				printf("Connection lost with P1\n");
				close(p1_socket);
				close(p2_socket);
				break ;
			}
			p1_move[r] = '\0';

			printf("Waiting for P2...\n");

			if ((r = recv(p2_socket, p2_move, 1024, 0)) < 1)
			{
				printf("Connection lost with P2\n");
				close(p1_socket);
				close(p2_socket);
				break ;
			}
			p2_move[r] = '\0';

			loop = 0;
			if (atoi(p1_move) == 1 && atoi(p2_move) == 2)
				sprintf(buffer, "Turn: %d\n(P1) Rock -|VS|- Paper (P2)\nP2 WINS !\n", turn);
			else if (atoi(p1_move) == 1 && atoi(p2_move) == 3)
				sprintf(buffer, "Turn: %d\n(P1) Rock -|VS|- Scissors (P2)\nP1 WINS !\n", turn);
			else if (atoi(p1_move) == 2 && atoi(p2_move) == 1)
				sprintf(buffer, "Turn: %d\n(P1) Paper -|VS|- Rock (P2)\nP1 WINS !\n", turn);
			else if (atoi(p1_move) == 2 && atoi(p2_move) == 3)
				sprintf(buffer, "Turn: %d\n(P1) Paper -|VS|- Scissors (P2)\nP2 WINS !\n", turn);
			else if (atoi(p1_move) == 3 && atoi(p2_move) == 1)
				sprintf(buffer, "Turn: %d\n(P1) Scissors -|VS|- Rock (P2)\nP2 WINS !\n", turn);
			else if (atoi(p1_move) == 3 && atoi(p2_move) == 2)
				sprintf(buffer, "Turn: %d\n(P1) Scissors -|VS|- Paper (P2)\nP1 WINS !\n", turn);
			else
			{
				loop = 1;
				sprintf(buffer, "Turn: %d\n(P1) %s -|VS|- %s (P2)\nMatch Null !\n", turn,
						get_move(atoi(p1_move)), get_move(atoi(p2_move)));
			}

			printf("%s", buffer);
			send(p1_socket, buffer, strlen(buffer), 0);
			send(p2_socket, buffer, strlen(buffer), 0);
		}
		close(p1_socket);
		close(p2_socket);
	}

	return 0;
}
