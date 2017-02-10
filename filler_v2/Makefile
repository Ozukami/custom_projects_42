# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/02/10 09:15:53 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = apoisson.filler
FLAGS = -Wall -Wextra -Werror
SRC = *.c

all: $(NAME)

$(NAME): libft.a $(SRC)
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(SRC) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

libft.a:
	@make -C libft/
	@mv libft/libft.a .
	@make clean -C libft/

test: $(NAME)
	@printf "\033[0;31m- Executing filler -\n\033[0m"
	@rm players/$(NAME)
	@cp $(NAME) players/
	@./filler_vm -f maps/custom_map -p1 players/$(NAME)
	@printf "\033[0;31m-- End of filler --\n\033[0m"

test_map: $(NAME)
	@printf "\033[0;31m- Executing filler -\n\033[0m"
	@cp $(NAME) players/
	@./filler_vm -f maps/$(ARGS) -p1 players/$(NAME) -p2 players/superjeannot.filler 
	@printf "\033[0;31m-- End of filler --\n\033[0m"

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean all
