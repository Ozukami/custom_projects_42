# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/02/08 11:21:08 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gate.exe
FLAGS = -Wall -Wextra -Werror
SRC = *.c

all: $(NAME)

$(NAME): libft.a $(SRC)
	@printf "\033[0;36m> Compiling Gate\033[0m"
	@gcc -o $(NAME) $(SRC) -L. -lft -lmlx -framework OpenGL -framework AppKit -I includes
	@printf "\033[0;32m OK\n\033[0m"

libft.a:
	@make -C libft/
	@mv libft/libft.a .
	@make clean -C libft/

gate: $(NAME)
	@printf "\033[0;31m- Executing Gate -\n\033[0m"
	@gcc -o $(NAME) $(SRC) -L. -lft -lmlx -framework OpenGL -framework AppKit -I includes
	@./gate.exe
	@printf "\033[0;31m-- End of Gate --\n\033[0m"

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean all
