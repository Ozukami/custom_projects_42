# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/03/28 23:41:24 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = apoisson.filler
FLAGS = -Wall -Wextra -Werror
LFTSRC = ft_absolute.c ft_memchr.c ft_strdel.c ft_atoi.c ft_memcmp.c ft_strdup.c ft_bspace.c ft_memcpy.c ft_strequ.c ft_bzero.c ft_memdel.c ft_striter.c ft_check_spaces.c ft_memmove.c ft_striteri.c ft_count_digit.c ft_memset.c ft_strjoin.c ft_fill_zero.c ft_min.c ft_strjoinf.c ft_isalnum.c ft_put_hex_fd.c ft_strlcat.c ft_isalpha.c ft_putchar.c ft_strlen.c ft_isascii.c ft_putchar_fd.c ft_strmap.c ft_isdigit.c ft_putendl.c ft_strmapi.c ft_islower.c ft_putendl_fd.c ft_strncat.c ft_isprint.c ft_putnbr.c ft_strncmp.c ft_isspace.c ft_putnbr_endl.c ft_strncpy.c ft_isupper.c ft_putnbr_fd.c ft_strnequ.c ft_itoa.c ft_putnbr_long.c ft_strnew.c ft_itoa_base.c ft_putnbr_short.c ft_strnstr.c ft_putnbr_u_int.c ft_strrchr.c ft_lltoa_base.c ft_putnbr_u_long.c ft_strrev.c ft_putnbr_u_short.c ft_strspace.c ft_lslen.c ft_putstr.c ft_strsplit.c ft_lstadd.c ft_putstr_fd.c ft_strstr.c ft_lstdel.c ft_recursive_power.c ft_strsub.c ft_lstdelone.c ft_strtrim.c ft_lstiter.c ft_strzero.c ft_lstmap.c ft_tolower.c ft_lstnew.c ft_straddchar.c ft_toupper.c ft_strcat.c ft_ulltoa_base.c ft_strchr.c ft_max.c ft_strclr.c ft_memalloc.c ft_strcmp.c ft_memccpy.c ft_strcpy.c get_next_line.c
SRC = free.c ft_info.c struct.c place.c get.c tools.c
MAIN = no_mlx.c
MLX = mlx.c draw.c display.c

all: $(NAME)

$(NAME): libft.a $(addprefix srcs/, $(SRC))
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(addprefix srcs/, $(SRC)) $(addprefix srcs/, $(MAIN)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

no_mlx: libft.a $(addprefix srcs/, $(SRC))
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(addprefix srcs/, $(SRC)) $(addprefix srcs/, $(MAIN)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

mlx: libft.a $(addprefix srcs/, $(SRC))
	@printf "\033[0;36m> Compiling filler\033[0m"
	@gcc $(FLAGS) -I includes/ -L. -lft $(addprefix srcs/, $(SRC)) $(addprefix srcs/, $(MLX)) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@printf "\033[0;32m OK\n\033[0m"

libft.a: $(addprefix libft/, $(LFTSRC))
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
	@./filler_vm -f maps/$(ARGS) -p1 players/carli.filler -p2 players/$(NAME)
	@printf "\033[0;31m-- End of filler --\n\033[0m"

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean all
