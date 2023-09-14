# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/09/14 20:16:42 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
C_FLAGS = 

SRCS = srcs/main.c	\
	srcs/lexer.c \
	srcs/tokenize.c \
	srcs/list.c \
	srcs/node.c \
	srcs/check_character_symbol.c \
	srcs/tokenize_utils_1.c \
	srcs/tokenize_utils_2.c \
	srcs/shell_signal.c	\
	srcs/block_signal.c \
	srcs/parser.c

OBJS = $(SRCS:%.c=%.o)
HEADER = includes/minishell.h


%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(SRCS) -o $@ -lreadline -lncurses mylib/mylib.a

all : $(NAME)

clean :
# make clean -C ./mylib
	rm -rf $(SRCS:%.c=%.o)

fclean : clean
# make fclean -C ./mylib
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re