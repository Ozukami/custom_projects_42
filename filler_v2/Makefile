# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/03/28 22:56:10 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = apoisson.filler
FLAGS = -Wall -Wextra -Werror
SRC = free.c ft_info.c struct.c place.c get.c tools.c
MAIN = no_mlx.c
MLX = mlx.c draw.c display.c

all: $(NAME)

$(NAME): libft.a $(addprefix srcs/, $(SRC))
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(addprefix srcs/, $(SRC)) $(addprefix srcs/, $(MAIN)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

mlx: libft.a $(addprefix srcs/, $(SRC))
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(addprefix srcs/, $(SRC)) $(addprefix srcs/, $(MLX)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

libft.a:
	@make -C libft/
	@mv libft/libft.a .
	@make clean -C libft/

test: $(NAME)
	@printf "\033[0;31m- Executing filler -\n\033[0m"
	@cp $(NAME) players/
	@./filler_vm -f maps/map02 -p1 players/$(NAME)
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
