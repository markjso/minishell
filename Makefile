# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarks <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 14:11:20 by jmarks            #+#    #+#              #
#    Updated: 2023/04/12 14:18:26 by jmarks           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=minishell.c \
	builtins.c \
	execmd.c \
	utils.c	\
	signal.c \
	cd_command.c \
	initialise.c

INCLUDE=-I$(LIBFT)
INCL_RL = /usr/local/opt/readline/include/
LINK_RL = /usr/local/opt/readline/lib

RM = rm -rf
	
OBJS=$(SRCS:.c=.o)

CC=gcc

LIBFT=libft/libft.a

CFLAGS=-Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CLFAGS) -L $(LINK_RL) -o $@ $^ -lreadline 
	@echo minishell is compiled

$(LIBFT):
		@$(MAKE) -C libft
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL_RL)

clean:
	@$(MAKE) clean -C libft
	@rm -f $(OBJS)

fclean:	clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
