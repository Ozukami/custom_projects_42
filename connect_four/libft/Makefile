# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/06/09 10:03:09 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_strequf_l.c ft_strsplitf.c str_epur.c ft_strsplit_whitespaces.c ft_perror.c tab_size.c free_map.c ft_my_printf.c ft_atol.c ft_strjoinf_l.c ft_strjoinf_r.c ft_strsubf.c ft_free_rect.c ft_absolute.c ft_memccpy.c ft_strdup.c ft_memchr.c ft_strequ.c ft_atoi.c ft_memcmp.c ft_striter.c ft_atoi_base.c ft_memcpy.c ft_striteri.c ft_bspace.c ft_memdel.c ft_strjoin.c ft_bzero.c ft_memmove.c ft_strjoinf.c ft_check_spaces.c ft_memset.c ft_strlcat.c ft_count_digit.c ft_min.c ft_strlen.c ft_fill_zero.c ft_new_coord.c ft_strmap.c ft_isalnum.c ft_new_rect.c ft_strmapi.c ft_isalpha.c ft_strncat.c ft_isascii.c ft_putchar.c ft_strncmp.c ft_isdigit.c ft_putchar_fd.c ft_strncpy.c ft_islower.c ft_putendl.c ft_strnequ.c ft_isprint.c ft_putendl_fd.c ft_strnew.c ft_isspace.c ft_putnbr.c ft_strnstr.c ft_isupper.c ft_putnbr_endl.c ft_strrchr.c ft_itoa.c ft_putnbr_fd.c ft_strrev.c ft_itoa_base.c ft_putstr.c ft_strspace.c ft_lltoa_base.c ft_putstr_fd.c ft_strsplit.c ft_lslen.c ft_recursive_power.c ft_strstr.c ft_lstadd.c ft_set_coord.c ft_strsub.c ft_lstdel.c ft_straddchar.c ft_strtrim.c ft_lstdelone.c ft_strcat.c ft_strzero.c ft_lstiter.c ft_strchr.c ft_tolower.c ft_lstmap.c ft_strclr.c ft_toupper.c ft_lstnew.c ft_strcmp.c ft_ulltoa_base.c ft_max.c ft_strcpy.c get_next_line.c ft_memalloc.c ft_strdel.c
OBJS = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[0;36m> Compiling libft\033[0m"
	@ar rc $(NAME) $(OBJS)
	@printf "\033[0;32m OK\n\033[0m"

$(OBJS):
	@gcc $(FLAGS) -c -g $(SRC) -I ../includes/

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
