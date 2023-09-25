# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/09/25 21:00:31 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
C_FLAGS = -I$(HEADER)
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
OTHER_DIR = srcs/other_dir

LEXER_SRCS = lexer.c \
	lexer_error.c \
	lexer_tokenize.c \
	lexer_list.c \
	lexer_free_list.c \
	lexer_node.c \
	lexer_check_character_symbol.c \
	lexer_check_is_close_quote.c \
	lexer_parse_pipe_or_orif_or_andif.c \
	lexer_tokenize_utils.c \
	lexer_make_value.c \
	lexer_count_quote_string.c \
	lexer_make_quote_string.c

PARSER_SRCS = parser.c \
	parser_error.c \
	parser_function_1.c \
	parser_function_2.c \
	parser_tree_node.c \
	parser_free_tree.c

OTHER_SRCS = main.c	\
	shell_signal.c	\
	terminal_option.c \
	blocking_signal.c

LEXER_OBJS = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS:.c=.o))
PARSER_OBJS = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS:.c=.o))
OTHER_OBJS = $(addprefix $(OTHER_DIR)/,$(OTHER_SRCS:.c=.o))

OBJS = $(LEXER_OBJS) $(PARSER_OBJS) $(OTHER_OBJS)
# OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(SRCS) -o $@ -lreadline -lncurses mylib/mylib.a

all : $(NAME)

clean :
# make clean -C ./mylib
	rm -rf $(OBJS)

fclean : clean
# make fclean -C ./mylib
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re