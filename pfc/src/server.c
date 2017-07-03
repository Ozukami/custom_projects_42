/****************** SERVER CODE ****************/

#include "pfc.h"

int 	main(int ac, char **av)
{
	int 		server_socket, p1_socket, p2_socket;
	char 		buffer[1024];
	t_sock		serverAddr;
	t_sock		serverStorage;
	socklen_t	addr_size;
	ssize_t		r;

	printf("| SERVER |\n");

	(void)av;
	if (!ac)
		return (0);

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		perror("");

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
		perror("");

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

		/*---- Send message to the socket of the incoming connection ----*/
		sprintf(buffer, " -- NEW GAME --\nRock - Paper - Scissors\n");
		send(p1_socket, buffer, strlen(buffer), 0);
		sprintf(buffer, " -- NEW GAME --\nRock - Paper - Scissors\n");
		send(p2_socket, buffer, strlen(buffer), 0);

		if ((r = recv(p1_socket, buffer, 1024, 0)) == -1)
			perror("");
		buffer[r] = '\0';
		printf("P1 move = %s\n", buffer);

		if ((r = recv(p2_socket, buffer, 1024, 0)) == -1)
			perror("");
		buffer[r] = '\0';
		printf("P2 move = %s\n", buffer);
	}

	return 0;
}
