# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/09/20 17:48:25 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
C_FLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c	\
	srcs/lexer.c \
	srcs/lexer_error.c \
	srcs/lexer_tokenize.c \
	srcs/lexer_list.c \
	srcs/lexer_free_list.c \
	srcs/lexer_node.c \
	srcs/lexer_check_character_symbol.c \
	srcs/lexer_parse_pipe_or_orif_or_andif.c \
	srcs/lexer_tokenize_utils_1.c \
	srcs/lexer_tokenize_utils_2.c \
	srcs/shell_signal.c	\
	srcs/block_signal.c \
	srcs/parser.c \
	srcs/parser_error.c \
	srcs/parser_function_1.c \
	srcs/parser_function_2.c \
	srcs/parser_tree_node.c \
	srcs/parser_free_tree.c

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