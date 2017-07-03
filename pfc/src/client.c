/****************** CLIENT CODE ****************/

#include "pfc.h"

void	check_winners(char *buffer, int id)
{
	if (strstr(buffer, "WINS"))
	{
		if (atoi(buffer + strlen(buffer) - 15) == id)
		{
			printf("\033[32mWON !\n\033[0m");
			system("afplay ressources/win_sound.aiff");
		}
		else
		{
			printf("\033[31mLOOSE !\n\033[0m");
			system("afplay ressources/loose_sound.aiff");
		}
		exit(0);
	}
}

int		main(int ac, char **av)
{
	int			player_id;
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
	serverAddr.sin_addr.s_addr = inet_addr("10.13.10.3");
	//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	printf("Connecting to the server...\n");

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	if (connect(client_socket, (struct sockaddr *) &serverAddr, addr_size))
		perror("");

	if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
		perror("");
	buffer[r] = '\0';
	player_id = atoi(buffer);

	printf("Connection OK (player ID = %d)\n", player_id);

	sprintf(buffer, "%s", av[1]);
	printf("Sending data to the server...\n");
	send(client_socket, buffer, strlen(buffer), 0);

	printf("Waiting for the server...\n");

	while ((r = recv(client_socket, buffer, 1024, 0)))
	{
		buffer[r] = '\0';
		printf("%s",buffer);

		check_winners(buffer, player_id);

		do
		{
			printf("1 : Rock\n2 : Paper\n3 : Scissors\n");
			scanf("%s", buffer);
		} while (atoi(buffer) != 1 && atoi(buffer) != 2 && atoi(buffer) != 3);
		send(client_socket, buffer, strlen(buffer), 0);
	}

	return 0;
}
