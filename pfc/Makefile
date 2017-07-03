# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/07/03 04:36:09 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra

all: server client

server: src/server.c
	@printf "\033[0;36m> Compiling Server\033[0m"
	@gcc $(FLAGS) -I includes -o server $^
	@printf "\033[0;32m OK\n\033[0m"

client: src/client.c
	@printf "\033[0;36m> Compiling Client\033[0m"
	@gcc $(FLAGS) -I includes -o client $^
	@printf "\033[0;32m OK\n\033[0m"

fclean:
	@rm -f server client

re: fclean all
