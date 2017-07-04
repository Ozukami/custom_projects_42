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

NAME = connect_four
FLAGS = -Wall -Wextra

all: $(NAME)

$(NAME): src/connect_four.c
	@printf "\033[0;36m> Compiling... \033[0m"
	@gcc $(FLAGS) -I includes -o $(NAME) $^
	@printf "\033[0;32mOK\n\033[0m"

fclean:
	@rm -f $(NAME)

re: fclean all
