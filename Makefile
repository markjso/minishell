# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarks <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 14:11:20 by jmarks            #+#    #+#              #
#    Updated: 2023/06/21 11:14:02 by jmarks           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=minishell.c \
	builtins.c \
	builtin_utils.c \
	execmd.c \
	utils.c	\
	signal.c \
	cd_command.c \
	environ.c \
	initialise.c \
	debug.c \
	process_input.c
	
dINCLUDE=-I$(LIBFT)
INCL_RL = /usr/local/opt/readline/include/
LINK_RL = /usr/local/opt/readline/lib

RM = rm -rf
	
OBJS=$(SRCS:.c=.o)
# OBJECT_FOLDER=objects

CC=gcc

LIBFT=libft/libft.a

CFLAGS=-Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -g -O0 $(CLFAGS) -L $(LINK_RL) -o $@ $^ -lreadline 
	# mkdir -p $(OBJECT_FOLDER)
	# mv $(OBJS) $(OBJECT_FOLDER)
	@echo minishell is compiled

$(LIBFT):
		@$(MAKE) -C libft
	
%.o: %.c
	@$(CC) -g -O0 $(CFLAGS) -c $< -o $@ -I $(INCL_RL)

clean:
	@$(MAKE) clean -C libft
	# @rm -rf $(OBJECT_FOLDER)
	@rm -f $(OBJS)

fclean:	clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
