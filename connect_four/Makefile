# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/07/12 00:40:44 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = connect_four
FLAGS = -Wall -Wextra

all: $(NAME)

$(NAME): src/connect_four.c libft.a
	@printf "\033[0;36m> Compiling connect_four... \033[0m"
	@gcc $(FLAGS) $^ -I includes -o $(NAME) -L. -lft
	@printf "\033[0;32mOK\n\033[0m"

libft.a:
	@make -C libft/
	@make clean -C libft/
	@mv libft/libft.a .

fclean:
	@rm -f libft.a
	@rm -f $(NAME)

re: fclean all
