# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/10/20 14:43:45 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
C_FLAGS = -I$(HEADER)
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
ENTRY_DIR = srcs/entry_dir
RUN_DIR = srcs/run_dir
SIGNAL_DIR = srcs/signal_dir
BUILTIN_DIR= srcs/builtin_dir
TEST_DIR = srcs/test_dir
WILD_CARD_DIR = srcs/wild_card_dir
HEREDOC_DIR = srcs/heredoc_dir

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

ENTRY_SRCS = temp_file.c
	
SIGNAL_SRCS = shell_signal.c \
	terminal_option.c \
	blocking_signal.c \
	heredoc_signal.c

BUILTIN_SRCS = builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export.c \
	builtin_pwd.c \
	builtin_unset.c \
	expand_env.c	\
	utils_check.c \
	utils_env.c \
	utils_etc.c \
	utils.c

RUN_SRCS = init_path_env-1.c \
	main.c \
	path.c \
	run_command.c \
	run_exe.c \
	run_fork.c \
	run_redir.c \
	run_root.c \
	run_utils.c	\
	ft_stderror_print.c

WILD_CARD_SRCS = wild_card.c \
	check_wild_card_pattern.c \
	wild_card_type_is_string.c

HEREDOC_SRCS = get_heredoc.c

TEST_SRCS = test.c

SRCS1 = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS))
SRCS2 = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
SRCS3 = $(addprefix $(RUN_DIR)/,$(RUN_SRCS))
SRCS4 = $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
SRCS5 = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRCS))
SRCS6 = $(addprefix $(TEST_DIR)/,$(TEST_SRCS))
SRCS7 = $(addprefix $(ENTRY_DIR)/,$(ENTRY_SRCS))
SRCS8 = $(addprefix $(WILD_CARD_DIR)/,$(WILD_CARD_SRCS))
SRCS9 = $(addprefix $(HEREDOC_DIR)/,$(HEREDOC_SRCS))

LEXER_OBJS = $(SRCS1:.c=.o)
PARSER_OBJS = $(SRCS2:.c=.o)
RUN_OBJS = $(SRCS3:.c=.o)
SIGNAL_OBJS = $(SRCS4:.c=.o)
BUILTIN_OBJS = $(SRCS5:.c=.o)
TEST_OBJS = $(SRCS6:.c=.o)
ENTRY_OBJS = $(SRCS6:.c=.o)
WILD_CARD_OBJS = $(SRCS7:.c=.o)
HEREDOC_OBJS = $(SRCS8:.c=.o)

OBJS = $(LEXER_OBJS) $(PARSER_OBJS) $(RUN_OBJS) $(SIGNAL_OBJS) $(BUILTIN_OBJS) $(TEST_OBJS) $(ENTRY_OBJS) $(WILD_CARD_OBJS) $(HEREDOC_OBJS)
# OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) $(SRCS7) $(SRCS8) $(SRCS9) -o $@ -lreadline -lncurses mylib/mylib.a

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

fast :
	make && make clean && clear

.PHONY : all clean fclean re fast