/****************** CLIENT CODE ****************/

#include "pfc.h"

int		main(int ac, char **av)
{
	int			client_socket;
	char		buffer[1024];
	t_sock		serverAddr;
	socklen_t	addr_size;
	ssize_t		r;

	printf("| CLIENT |\n");

	if (ac < 2)
		return (0);

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
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

	printf("Connecting to the server...\n");

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	if (connect(client_socket, (struct sockaddr *) &serverAddr, addr_size))
		perror("");

	printf("Connection OK\n");

	sprintf(buffer, "%s", av[1]);
	printf("Sending data to the server...\n");
	send(client_socket, buffer, strlen(buffer), 0);

	printf("Waiting for the server...\n");

	/*---- Read the message from the server into the buffer ----*/
	while ((r = recv(client_socket, buffer, 1024, 0)))
	{
		buffer[r] = '\0';
		printf("%s",buffer);

		scanf("%s", buffer);
		send(client_socket, buffer, strlen(buffer), 0);
	}

	return 0;
}
