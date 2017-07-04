
#include "connect_four.h"

void exit_perror(char *error)
{
	if (!error)
		perror("");
	else
		perror(error);
	exit(0);
}

void host_game(void)
{
	int 			server_socket, client_socket;
	char 			buffer[BUFF_SIZE + 1];
	t_sock		serverAddr;
	t_sock		serverStorage;
	socklen_t	addr_size;
	ssize_t		r;
	int				op_val = 1;

	printf("HOSTING A GAME\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
	if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		exit_perror("socket");
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &op_val, sizeof(int)) < 0)
		exit_perror("setsockopt");
	if (bind(server_socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)))
		exit_perror("bind");
	addr_size = sizeof(serverStorage);
	if (listen(server_socket, 1) < 0)
		exit_perror("listen");
	printf("Waiting for a player...\n");
	if ((client_socket = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size)) < 0)
		exit_perror("accept");
	if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
		exit_perror("recv");
	buffer[r] = '\0';
	printf("Player %s has joined !\n", buffer);
}

void connect_to_host(void)
{
	int				client_socket;
	char			buffer[BUFF_SIZE + 1];
	t_sock		serverAddr;
	socklen_t	addr_size;
	ssize_t		r;

	printf("CONNECTING TO A GAME\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
	if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		exit_perror("socket");
	addr_size = sizeof serverAddr;
	printf("Connecting to the game...\n");
	if (connect(client_socket, (struct sockaddr *) &serverAddr, addr_size))
		exit_perror("connect");
	printf("Enter a Pseudo\n");
	scanf("%s", buffer);
	if (send(client_socket, buffer, strlen(buffer), 0) < 0)
		exit_perror("send");
	printf("Waiting for the server...\n");
}

void versus_ia(void)
{
	printf("VS IA\n");
}

int	check_choice(int i)
{
	if (i == 1 || i == 2 || i == 3 || i == 4)
		return (0);
	return (1);
}

void menu(void)
{
	char	choice[128];

	do {
		system("clear");
		printf("o --- MENU --- o\n");
		printf("|  1 : HOST    |\n");
		printf("|  2 : CONNECT |\n");
		printf("|  3 : VS IA   |\n");
		printf("|  4 : EXIT    |\n");
		printf("o ------------ o\n");
		scanf("%s", choice);
	} while(check_choice(atoi(choice)));
	printf("Choix: %s\n", choice);
	if (atoi(choice) == 1)
		host_game();
	if (atoi(choice) == 2)
		connect_to_host();
	if (atoi(choice) == 3)
		versus_ia();
	if (atoi(choice) == 4)
		exit(0);
}

int 	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	menu();
	return 0;
}
