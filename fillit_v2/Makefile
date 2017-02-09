# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apoisson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:29:15 by apoisson          #+#    #+#              #
#    Updated: 2017/02/08 23:46:13 by apoisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIB = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_mlx.c ft_process.c ft_back_tracking.c ft_exit.c ft_tetrilist.c ft_verif.c ft_check.c ft_init.c ft_format.c
LIBSRC = ft_sqrt.c ft_atoi.c ft_lstnew.c ft_putnbr_fd.c ft_strmapi.c ft_bzero.c ft_putstr.c ft_strncat.c ft_check_spaces.c ft_max.c ft_putstr_fd.c ft_strncmp.c ft_isalnum.c ft_memalloc.c ft_strcat.c ft_strncpy.c ft_isalpha.c ft_memccpy.c ft_strchr.c ft_strnequ.c ft_isascii.c ft_memchr.c ft_strclr.c ft_strnew.c ft_isdigit.c ft_memcmp.c ft_strcmp.c ft_strnstr.c ft_islower.c ft_memcpy.c ft_strcpy.c ft_strrchr.c ft_isprint.c ft_memdel.c ft_strdel.c ft_strrev.c ft_isspace.c ft_memmove.c ft_strdup.c ft_strsplit.c ft_isupper.c ft_memset.c ft_strequ.c ft_strstr.c ft_itoa.c ft_min.c ft_striter.c ft_strsub.c ft_lstadd.c ft_putchar.c ft_striteri.c ft_strtrim.c ft_lstdel.c ft_putchar_fd.c ft_strjoin.c ft_tolower.c ft_lstdelone.c ft_putendl.c ft_strlcat.c ft_toupper.c ft_lstiter.c ft_putendl_fd.c ft_strlen.c ft_lstmap.c ft_putnbr.c ft_strmap.c
LIBOBJ = $(LIBSRC:.c=.o)
HEADERS = ./includes

all: $(NAME)

$(NAME): $(LIB)
	@gcc $(FLAGS) $(addprefix srcs/, $(SRC)) srcs/$(NAME).c -o $(NAME) -I $(HEADERS) -L. -lft -lmlx -framework OpenGL -framework AppKit

$(LIB):
	@gcc $(FLAGS) -c $(addprefix libft/, $(LIBSRC)) -I $(HEADERS)
	@test -d objs || mkdir objs
	@mv $(LIBOBJ) objs/
	@ar rc $(LIB) $(addprefix objs/, $(LIBOBJ))

clean:
	@rm -rdf objs/

lclean:
	@rm -f $(LIB)

fclean: lclean clean
	@rm -f $(NAME)

re: fclean all
