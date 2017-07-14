/****************** CLIENT CODE ****************/
#include "libft.h"
#include "chat.h"

int		main(int ac, char **av)
{
	int			player_id;
	int			client_socket;
	char		buffer[1024];
	t_sock		serverAddr;
	socklen_t	addr_size;
	ssize_t		r;
	char		name[120];
	int		accepted;

	printf("| CLIENT |\n");

	accepted = 0;
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
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
	//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	printf("Connecting to the server...\n");
	printf("Enter a name:\n");

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	if (connect(client_socket, (struct sockaddr *) &serverAddr, addr_size))
		perror("ICI");
	while (!accepted)
	{
		scanf("%s", buffer);
		strcpy(name, buffer);
		buffer[strlen(buffer) + 1] = '\0';
		if (send(client_socket, buffer, strlen(buffer), 0) < 1)
			perror("LA");
		if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
			perror("");
		if (strstr(buffer, name))
		{
			printf("You are connected as %s\n", name);
			accepted = 1;
		}
		else
		{
			printf("A chater already called himself %s, please pick an other name\n", name);
			buffer[0] = '\0';
			name[0] = '\0';
		}
	}
	while (1)
	{
		printf("Type your message:\n");
		do
		{
			scanf("%s", buffer);
		} while (!buffer[0]);
		buffer[strlen(buffer) + 1] = '\0';
		if (send(client_socket, buffer, strlen(buffer), 0) < 0)
			perror("");
		if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
			perror("");
		printf("%s\n", buffer);
	}
	return (0);
}
