# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/02/07 00:30:01 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = get_next_line.c ft_atoi.c  ft_lstnew.c  ft_putnbr_u_int.c ft_strlen.c ft_bspace.c  ft_ltoa_base.c  ft_putnbr_u_long.c ft_strmap.c ft_bzero.c  ft_ltoa_unsigned.c ft_putnbr_u_short.c ft_strmapi.c ft_check_spaces.c ft_max.c  ft_putstr.c  ft_strncat.c ft_isalnum.c  ft_memalloc.c  ft_putstr_fd.c  ft_strncmp.c ft_isalpha.c  ft_memccpy.c  ft_recursive_power.c ft_strncpy.c ft_isascii.c  ft_memchr.c  ft_sstoa.c  ft_strnequ.c ft_isdigit.c  ft_memcmp.c  ft_stoa_base.c  ft_strnew.c ft_islower.c  ft_memcpy.c  ft_stoa_unsigned.c ft_strnstr.c ft_isprint.c  ft_memdel.c  ft_straddchar.c  ft_strrchr.c ft_isspace.c  ft_memmove.c  ft_strcat.c  ft_strrev.c ft_isupper.c  ft_memset.c  ft_strchr.c  ft_strspace.c ft_itoa.c  ft_min.c  ft_strclr.c  ft_strsplit.c ft_itoa_base.c  ft_put_hex_fd.c  ft_strcmp.c  ft_strstr.c ft_itoa_unsigned.c ft_putchar.c  ft_strcpy.c  ft_strsub.c ft_lltoa_base.c  ft_putchar_fd.c  ft_strdel.c  ft_strtrim.c ft_lltoa_unsigned.c ft_putendl.c  ft_strdup.c  ft_tolower.c ft_lslen.c  ft_putendl_fd.c  ft_strequ.c  ft_toupper.c ft_lstadd.c  ft_putnbr.c  ft_striter.c  ft_ulltoa_base.c ft_lstdel.c  ft_putnbr_endl.c ft_striteri.c  ft_ultoa_base.c ft_lstdelone.c  ft_putnbr_fd.c  ft_strjoin.c  ft_ultoa_base_2.c ft_lstiter.c  ft_putnbr_long.c ft_strjoinf.c  ft_usstoa_base.c ft_lstmap.c  ft_putnbr_short.c ft_strlcat.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[0;36m> Compiling libft\033[0m"
	@ar rc $(NAME) $(OBJS)
	@printf "\033[0;32m OK\n\033[0m"

$(OBJS):
	@gcc $(FLAGS) -c $(SRC) -I ../includes/

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
