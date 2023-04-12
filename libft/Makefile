# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarks <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 09:56:06 by jmarks            #+#    #+#              #
#    Updated: 2022/06/08 10:53:17 by jmarks           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

#######################LIBFT############
SRC_LIBFT=	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c	\
	ft_strjoin.c \
	ft_itoa.c \
	ft_strtrim.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_putstr_fd.c \
	ft_putchar_fd.c \
	ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_split.c \

SRC_LIBFT_D=$(addprefix libft/,$(SRC_LIBFT))
######################## PRINTF###################

SRC_PRINTF=ft_printf.c \
	ft_printf_char.c \
	ft_printf_hex.c \
	ft_printf_number.c \
	ft_printf_str.c \
	ft_type_char.c \
	ft_printf_ptr.c \
	ft_printf_u.c \

SRC_PRINTF_D=$(addprefix printf/,$(SRC_PRINTF))
####################################################

CC=gcc

CFLAGS=-Wall -Wextra -Werror

INC=-I ./inc

SRC=$(SRC_LIBFT) $(SRC_PRINTF)

SRC_D=$(addprefix src/,$(SRC_LIBFT_D) $(SRC_PRINTF_D))

OBJS=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_D)
	$(CC) $(CFLAGS) -c $(SRC_D) $(INC)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
