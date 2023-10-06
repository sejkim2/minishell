# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/10/06 20:06:53 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
C_FLAGS = -I$(HEADER)
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
UTILS_DIR = srcs/utils_dir
SIGNAL_DIR = srcs/signal_dir
BUILTIN_DIR= srcs/builtin_dir
TEST_DIR = srcs/test_dir

LEXER_SRCS = lexer.c \
	lexer_error.c \
	tokenize.c \
	list_utils.c \
	free_list.c \
	list_node_utils.c \
	check_character_symbol_utils.c \
	parse_pipe_or_orif_or_andif.c \
	parse_redirection.c \
	parse_quote_string.c \
	parse_word_or_branket.c \
	make_value.c \
	quote_utils.c \
	make_quote_string.c

PARSER_SRCS = parser.c \
	parser_error.c \
	parser_function_1.c \
	parser_function_2.c \
	tree_node_utils.c \
	free_tree.c \
	parser_utils.c

UTILS_SRCS = main.c	\
	temp_file.c \
	exec.c
	
SIGNAL_SRCS = shell_signal.c \
	terminal_option.c \
	blocking_signal.c \
	heredoc_signal.c

BUILTIN_SRCS = check_env_utils.c \
	get_exit_code.c \
	func_cd.c \
	func_echo.c \
	func_env.c \
	func_exit.c \
	func_export.c \
	func_pwd.c \
	func_unset.c \
	func_utils.c \
	make_env_utils.c

TEST_SRCS = test.c

SRCS1 = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS))
SRCS2 = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
SRCS3 = $(addprefix $(UTILS_DIR)/,$(UTILS_SRCS))
SRCS4 = $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
SRCS5 = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRCS))
SRCS6 = $(addprefix $(TEST_DIR)/,$(TEST_SRCS))

LEXER_OBJS = $(SRCS1:.c=.o)
PARSER_OBJS = $(SRCS2:.c=.o)
UTILS_OBJS = $(SRCS3:.c=.o)
SIGNAL_OBJS = $(SRCS4:.c=.o)
BUILTIN_OBJS = $(SRCS5:.c=.o)
TEST_OBJS = $(SRCS6:.c=.o)

OBJS = $(LEXER_OBJS) $(PARSER_OBJS) $(UTILS_OBJS) $(SIGNAL_OBJS) $(BUILTIN_OBJS) $(TEST_OBJS)
# OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) -o $@ -lreadline -lncurses mylib/mylib.a

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