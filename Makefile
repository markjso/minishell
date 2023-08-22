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
	cmd_linked_list.c \
	cmd_linked_list_delete.c \
	environ.c \
	environ_utils.c \
	initialise.c \
	process_input.c \
	token_linked_list.c \
	token_linked_list_create.c \
	variable.c \
	variable_expand_utils.c \
	process_input_utils.c \
	remove_quotes.c \
	string_utils_1.c \
	string_utils_2.c \
	error.c \
	redirection.c \
	redirection_utils.c \
	heredoc.c \
	pipes.c \
	exit_and_free.c
	
dINCLUDE=-I$(LIBFT)
INCL_RL = /usr/local/opt/readline/include/
LINK_RL = /usr/local/opt/readline/lib

RM = rm -rf
	
OBJS=$(SRCS:.c=.o)

CC=gcc

LIBFT=libft/libft.a

CFLAGS=-Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -g -O0 $(CLFAGS) -L $(LINK_RL) -o $@ $^ -lreadline 
	@echo minishell is compiled

$(LIBFT):
		$(MAKE) -C libft
	
%.o: %.c
	$(CC) -g -O0 $(CFLAGS) -c $< -o $@ -I $(INCL_RL)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJS)

fclean:	clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
