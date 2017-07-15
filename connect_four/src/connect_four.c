#include "connect_four.h"

void	exit_perror(char *error)
{
	if (!error)
		perror("");
	else
		perror(error);
	exit(0);
}

void	display_game(t_game *game)
{
	int		i;
	int		j;
	char	piece;

	piece = ' ';
	system("clear");
	printf("._____._____._____._____._____._____._____.\n");
	i = -1;
	while (++i < 6)
	{
		printf("|     |     |     |     |     |     |     |\n");
		j = -1;
		while (++j < 7)
		{
			if (TRAY[i][j] == 1)
				printf("|  %so%s  ", CYAN, DEFAULT);
			else if (TRAY[i][j] == 2)
				printf("|  %so%s  ", PURPLE, DEFAULT);
			else if (TRAY[i][j] == 0)
				printf("|     ");
			else
				printf("|  x  ");
			if (j == 6)
				printf("|\n");
			printf(DEFAULT);
		}
		printf("|_____|_____|_____|_____|_____|_____|_____|\n");
	}
	printf("   1     2     3     4     5     6     7\n");
}

t_player	*new_player(char *pseudo, int id, int host, int socket)
{
	t_player	*player;
	int			i;

	player = ft_memalloc(sizeof(t_player));
	player->id = id;
	player->pseudo = ft_strdup(pseudo);
	player->is_host = host;
	player->socket = socket;
	if (id == 3)
	{
		printf("IA !\n");
		player->id = 1;
		if (!(player->map_analyse = ft_memalloc(sizeof(int *) * 7)))
			exit_perror("Malloc failed");
		i = -1;
		while (++i < 8)
			if (!((player->map_analyse)[i] = ft_memalloc(sizeof(int) * 8)))
				exit_perror("Malloc failed");
	}
	return (player);
}

void	update_game(t_game *game, int col, int p)
{
	int		i;

	i = 6;
	while (--i >= 0)
	{
		if (TRAY[i][col] == 0)
		{
			TRAY[i][col] = p;
			display_game(game);
			return ;
		}
	}
}

int		check_line(t_game *game, int j, int p)
{
	int		i;
	int		n;

	i = -1;
	while (++i < 6)
		if (TRAY[i][j] == p)
			break ;
	n = 0;
	j = -1;
	while (++j < 7)
	{
		if (TRAY[i][j] == p)
			n++;
		else
			n = 0;
		if (n == 4)
			return (p);
	}
	return (0);
}

int		check_column(t_game *game, int j, int p)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (++i < 6)
	{
		if (TRAY[i][j] == p)
			n++;
		else
			n = 0;
		if (n == 4)
			return (p);
	}
	return (0);
}

int		check_diago_l(t_game *game, int j, int p)
{

	int		i;
	int		n;

	i = -1;
	while (++i < 6)
		if (TRAY[i][j] == p)
			break ;
	n = 0;
	while (i > 0 && j < 7)
	{
		i--;
		j++;
	}
	while (i <= 5 && j >= 0)
	{
		if (TRAY[i][j] == p)
			n++;
		else
			n = 0;
		if (n == 4)
			return (p);
		i++;
		j--;
	}
	return (0);
}

int		check_diago_r(t_game *game, int j, int p)
{

	int		i;
	int		n;

	i = -1;
	while (++i < 6)
		if (TRAY[i][j] == p)
			break ;
	n = 0;
	while (i > 0 && j > 0)
	{
		i--;
		j--;
	}
	while (i <= 5 && j <= 6)
	{
		if (TRAY[i][j] == p)
			n++;
		else
			n = 0;
		if (n == 4)
			return (p);
		i++;
		j++;
	}
	return (0);
}

int		tray_is_full(t_game *game)
{
	int		j;

	j = -1;
	while (++j < 7)
		if (TRAY[0][j] == 0)
			return (0);
	return (-1);
}

int		check_winner(t_game *game, int j, int p)
{
	int		rep;

	if ((rep = check_line(game, j, p)))
		return (rep);
	if ((rep = check_column(game, j, p)))
		return (rep);
	if ((rep = check_diago_r(game, j, p)))
		return (rep);
	if ((rep = check_diago_l(game, j, p)))
		return (rep);
	if ((rep = tray_is_full(game)))
		return (rep);
	return (0);
}

int		send_choice(t_game *game, int client_socket, int p)
{
	char 		*buffer;

	do
	{
		do
		{
			display_game(game);
			printf("Chose a column : [1-7]\n");
			get_next_line(0, &buffer);
		} while (atoi(buffer) < 1 || atoi(buffer) > 7);
	} while (TRAY[0][atoi(buffer) - 1] != 0);
	if (send(client_socket, buffer, ft_strlen(buffer), 0) < 0)
		exit_perror("send");
	update_game(game, atoi(buffer) - 1, p);
	return (atoi(buffer) - 1);
}

void	display_winner(t_game *game, int winner, int p)
{
	if (winner == -1)
	{
		printf("%sNO WINNER%s\n", RED, DEFAULT);
		system("afplay ressources/aiff/wihlelm.aiff");
		return ;
	}
	printf(CYAN);
	if (winner == 2)
		printf(PURPLE);
	printf("The Winner is %s !%s\n", ((winner == 1) ? P1_PSEUDO : P2_PSEUDO), DEFAULT);
	if (winner == p)
		system("afplay ressources/aiff/win_sound.aiff");
	else
		system("afplay ressources/aiff/loose_sound.aiff");
}

void	start_new_game(t_game *game, int client_socket)
{
	char 		buffer[BUF_SIZE + 1];
	int			winner;
	ssize_t		r;
	int			j;

	display_game(game);
	while (1)
	{
		j = send_choice(game, client_socket, 1);
		if ((winner = check_winner(game, j, 1)))
			break ;
		if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
			exit_perror("recv");
		update_game(game, atoi(buffer) - 1, 2);
		if ((winner = check_winner(game, atoi(buffer) - 1, 2)))
			break ;
	}
	display_winner(game, winner, 1);
}

void	play_v_host(t_game *game, int client_socket)
{
	char		buffer[BUF_SIZE + 1];
	ssize_t		r;
	int			winner;
	int			j;

	display_game(game);
	while (1)
	{
		if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
			exit_perror("recv");
		update_game(game, atoi(buffer) - 1, 1);
		if ((winner = check_winner(game, atoi(buffer) - 1, 1)))
			break ;
		j = send_choice(game, client_socket, 2);
		if ((winner = check_winner(game, j, 2)))
			break ;
	}
	display_winner(game, winner, 2);
}

void	host_game(t_game *game)
{
	int 		server_socket, client_socket;
	char 		buffer[BUF_SIZE + 1];
	t_sock		serverAddr;
	t_sock		serverStorage;
	socklen_t	addr_size;
	ssize_t		r;
	int			op_val = 1;

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
	printf("Enter a Pseudo\n");
	scanf("%s", buffer);
	P1 = new_player(buffer, 1, 1, server_socket);
	printf("P1 : %s\n", buffer);
	if (listen(server_socket, 1) < 0)
		exit_perror("listen");
	printf("[SYSTEM] Waiting for a player...\n");
	if ((client_socket = accept(server_socket, (struct sockaddr *) &serverStorage, &addr_size)) < 0)
		exit_perror("accept");
	if (send(client_socket, buffer, strlen(buffer), 0) < 0)
		exit_perror("send");
	if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
		exit_perror("recv");
	buffer[r] = '\0';
	printf("[SYSTEM] Player %s has joined !\n", buffer);
	P2 = new_player(buffer, 2, 0, client_socket);
	start_new_game(game, client_socket);
	close(server_socket);
	close(client_socket);
}

void connect_to_host(t_game *game)
{
	int			client_socket;
	char		buffer[BUF_SIZE + 1];
	t_sock		serverAddr;
	socklen_t	addr_size;
	ssize_t		r;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
	if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		exit_perror("socket");
	addr_size = sizeof serverAddr;
	printf("[SYSTEM] Connecting to the game...\n");
	if (connect(client_socket, (struct sockaddr *) &serverAddr, addr_size))
		exit_perror("connect");
	if ((r = recv(client_socket, buffer, 1024, 0)) < 1)
		exit_perror("recv");
	printf("[SYSTEM] Connected to : %s\n", buffer);
	P1 = new_player(buffer, 1, 1, client_socket);
	printf("Enter a Pseudo\n");
	scanf("%s", buffer);
	P2 = new_player(buffer, 2, 0, client_socket);
	if (send(client_socket, buffer, strlen(buffer), 0) < 0)
		exit_perror("send");
	printf("[SYSTEM] Waiting for the server...\n");
	play_v_host(game, client_socket);
	close(client_socket);
}

/*
void	start_ia(t_game *game)
{
	int		i;

	if (!(IA = ft_memalloc(sizeof(t_ia))))
		exit_perror("Malloc failed");
	if (!(IA_MAP = ft_memalloc(sizeof(int *) * 7)))
		exit_perror("Malloc failed");
	i = -1;
	while (++i < 8)
		if (!(IA_MAP[i] = ft_memalloc(sizeof(int) * 8)))
			exit_perror("Malloc failed");
	IA_ID = 1;
}
*/

/* TODO ia algo*/

int		line_ia(t_game *game, int x, int y)
{
	int		allies;
	int		ennemies;
	int		allies2;
	int		ennemies2;
	int		turn;
	int		x2;

	allies = 0;
	ennemies = 0;
	allies2 = 0;
	ennemies2 = 0;
	turn = 0;
	x2 = x;
	while (++turn < 4 && ++x <= 6)
	{
		if (turn == 1 && !TRAY[y][x])
			break ;
		if (TRAY[y][x] == IA_ID && !ennemies)
			allies += 3;
		else if (TRAY[y][x] == 2 && !allies)
			ennemies += 2;
	}
	turn = 0;
	while (++turn < 4 && --x2 >= 0)
	{
		if (turn == 1 && !TRAY[y][x2])
			break ;
		if (TRAY[y][x2] == IA_ID && !ennemies2)
			allies2 += 3;
		else if (TRAY[y][x2] == 2 && !allies2)
			ennemies2 += 2;
	}
	printf("ALLIES %d\n", allies2);
	//sleep(3);
	if (allies == 9 || allies2 == 9)
		return (120);
	else if (ennemies == 6 || ennemies2 == 6)
		return (90);
	ennemies += ennemies2;
	allies += allies2;
	if (ennemies < allies)
		return (allies);
	return (ennemies);
}

int		diago_l_ia(t_game *game, int x, int y)
{
	int		allies;
	int		allies2;
	int		ennemies;
	int		ennemies2;
	int		turn;
	int		x2;
	int		y2;

	allies = 0;
	allies2 = 0;
	ennemies = 0;
	ennemies2 = 0;
	turn = 0;
	x2 = x;
	y2 = y;
	while (++turn < 4 && ++y < 6 && --x >= 0)
	{
		if (TRAY[y][x] == IA_ID && !ennemies)
			allies += 3;
		else if (TRAY[y][x] == 2 && !allies)
			ennemies += 2;
	}
	turn = 0;
	while (++turn < 4 && --y2 >= 0 && --x2 >= 0)
	{
		if (TRAY[y2][x2] == IA_ID && !ennemies)
			allies2 += 3;
		else if (TRAY[y2][x2] == 2 && !allies)
			ennemies2 += 2;
	}
	//sleep(3);
	if (allies == 9 || allies2 == 9)
		return (120);
	else if (ennemies == 6 || ennemies2 == 6)
		return (90);
	ennemies += ennemies2;
	allies += allies2;
	if (ennemies < allies)
		return (allies);
	return (ennemies);
}

int		diago_r_ia(t_game *game, int x, int y)
{
	int		allies;
	int		allies2;
	int		ennemies;
	int		ennemies2;
	int		turn;
	int		x2;
	int		y2;

	allies = 0;
	allies2 = 0;
	ennemies = 0;
	ennemies2 = 0;
	turn = 0;
	x2 = x;
	y2 = y;
	while (++turn < 4 && ++y < 6 && ++x <= 6)
	{
		if (TRAY[y][x] == IA_ID && !ennemies)
			allies += 3;
		else if (TRAY[y][x] == 2 && !allies)
			ennemies += 2;
	}
	turn = 0;
	while (++turn < 4 && --y2 >= 0 && ++x2 <= 6)
	{
		if (TRAY[y2][x2] == IA_ID && !ennemies)
			allies2 += 3;
		else if (TRAY[y2][x2] == 2 && !allies)
			ennemies2 += 2;
	}
	//sleep(3);
	if (allies == 9 || allies2 == 9)
		return (120);
	else if (ennemies == 6 || ennemies2 == 6)
		return (90);
	ennemies += ennemies2;
	allies += allies2;
	if (ennemies < allies)
		return (allies);
	return (ennemies);
}

int		column_ia(t_game *game, int x, int y)
{
	int		allies;
	int		ennemies;
	int		turn;

	allies = 0;
	ennemies = 0;
	turn = 0;
	while (++turn < 4 && ++y < 6)
	{
		if (turn == 1 && !TRAY[y][x])
			return (0);
		else if (TRAY[y][x] == IA_ID && !ennemies)
			allies += 3;
		else if (TRAY[y][x] == 2 && !allies)
			ennemies += 2;
	}
	//sleep(3);
	if (allies == 9)
		return (120);
	else if (ennemies == 6)
		return (90);
	if (ennemies < allies)
		return (allies);
	return (ennemies);
}

void	analyse_map(t_game *game)
{
	int	x;
	int	y;
	int	rep;

	rep = 0;
	x = -1;
	while (++x <= 6)
	{
		y = 0;
		while (y < 6 && TRAY[y][x] == 0)	
			y++;
		if (y > 1)
		{
			y -= 1;
			rep += column_ia(game, x, y);
			rep += line_ia(game, x, y);
			rep += diago_l_ia(game, y, x);
			rep += diago_r_ia(game, y, x);
		}
		IA_MAP[y][x] = rep;
		rep = 0;
	}
}

void	reset_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 6)
	{
		x = -1;
		while (++x <= 6)
			IA_MAP[y][x] = 0;
	}
}

int	set_answer(t_game *game)
{
	int	x;
	int	y;
	int	value;
	int	r;

	r = 0;
	value = 0;
	y = -1;
	while (++y < 6)
	{
		x = -1;
		while (++x <= 6)
		{
			if (IA_MAP[y][x] > value)
			{
				printf("\n\n    || IA_MAP[%d][%d] = %d \n\n", y, x, IA_MAP[y][x]);
				r = x + 1;
				printf("R = %d\n", r);
				value = IA_MAP[y][x];
			}
		}
	}
	reset_map(game);
	return (r);
}

int	ia_process2(t_game *game)
{
	int	rep;
	static int turn = 0;

	turn++;
	if (turn == 1)
		return (4);
	analyse_map(game);

	int	y = -1;
	int	x = -1;

	while (++y < 6)
	{
		x = -1;
		while (++x <= 6)
			printf("| %d |", IA_MAP[y][x]);
		printf("\n");
	}
	rep = set_answer(game);
	printf("ANSWER = { %d }\n", rep);
	//sleep (5);
	return (rep);
}

int	ia_process(void)
{
	static int turn = 0;

	turn++;
	if (turn == 3)
		turn = 8;
	if (turn > 7)
		turn = 1;
	return (turn);
}

void	versus_ia(t_game *game)
{
	char	*buffer;
	int		winner;
	int		ia_answer;

	printf("VS IA [Work in Progress]\n");
	P1 = new_player("IA", 3, 0, 0);
	printf("Enter a Pseudo\n");
	get_next_line(0, &buffer);
	P2 = new_player(buffer, 2, 0, 0);
	//start_ia(game);
	ia_answer = 2;
	while (1)
	{
		/*
		//ia_answer = ia_process();
		printf("START PROCESS2\n");
		ia_answer = ia_process2(game);
		printf("END PROCESS2\n");
		*/
		// IA TURN
		do
		{
			//ia_answer++;
			//ia_answer = ia_answer % 7;
			ia_answer = ia_process2(game) - 1;
			printf("%s%d%s\n", RED, ia_answer, DEFAULT);
		} while (TRAY[0][ia_answer] != 0);
		update_game(game, ia_answer, IA_ID);
		if ((winner = check_winner(game, ia_answer, IA_ID)))
			break ;
		do
		{
			do
			{
				printf("Chose a column : [1-7]\n");
				get_next_line(0, &buffer);
			} while (atoi(buffer) < 1 || atoi(buffer) > 7);
		} while (TRAY[0][atoi(buffer) - 1] != 0);
		update_game(game, atoi(buffer) - 1, P2_ID);
		if ((winner = check_winner(game, atoi(buffer) - 1, 2)))
			break ;
	}
	display_winner(game, winner, 2);
}

int	check_choice(int i)
{
	if (i == 1 || i == 2 || i == 3 || i == 4)
		return (0);
	return (1);
}

t_game	*new_game()
{
	t_game	*game;
	int		i;

	game = ft_memalloc(sizeof(t_game));
	TRAY = ft_memalloc(sizeof(int *) * 6);
	i = -1;
	while (++i < 6)
		TRAY[i] = ft_memalloc(sizeof(int) * 7);
	P1 = NULL;
	P2 = NULL;
	return (game);
}

void	free_game(t_game *game)
{
	ft_strdel(&P1_PSEUDO);
	free(P1);
	ft_strdel(&P2_PSEUDO);
	free(P2);
	// free tray
}

void	menu(void)
{
	char	choice[128];
	t_game	*game;

	game = new_game();
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
		host_game(game);
	if (atoi(choice) == 2)
		connect_to_host(game);
	if (atoi(choice) == 3)
		versus_ia(game);
	if (atoi(choice) == 4)
		exit(0);
	//free_game(game);
	exit (0);
}

int 	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	while (1)
		menu();
	return 0;
}
