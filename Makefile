# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/10/25 19:22:12 by jaehyji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
C_FLAGS = -I$(HEADER)
BUILTIN_DIR = srcs/builtin_dir
ENTRY_DIR = srcs/entry_dir
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
RUN_DIR = srcs/run_dir
SIGNAL_DIR = srcs/signal_dir
TEST_DIR = srcs/test_dir
WILD_CARD_DIR = srcs/wild_card_dir
HEREDOC_DIR = srcs/heredoc_dir

BUILTIN_SRCS = builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export.c \
	builtin_pwd.c \
	builtin_unset.c \
	builtin_utils.c \
	check_env_rule.c \
	env_utils.c \
	expand_env_utils.c \
	free_utils.c

LEXER_SRCS = check_character_symbol_utils.c \
	free_list.c \
	lexer_error.c \
	lexer.c \
	list_node_utils.c \
	list_utils.c \
	make_quote_string.c \
	make_value.c \
	parse_pipe_or_orif_or_andif.c \
	parse_quote_string.c \
	parse_redirection.c \
	parse_word_or_branket.c \
	quote_utils.c \
	tokenize.c

PARSER_SRCS = free_tree.c \
	parser_error.c \
	parser_function_1.c \
	parser_function_2.c \
	parser.c \
	tree_node_utils.c \
	parser_utils.c
	
RUN_SRCS = get_path.c \
	path_utils.c \
	run_command.c \
	run_exe.c \
	run_list.c \
	run_pipeline.c \
	run_redir_utils.c \
	run_redir.c \
	run_root.c \
	run_simple_command.c \
	cmd_utils.c \
	std_utils.c \
	exit_utils.c

SIGNAL_SRCS = blocking_signal.c \
	heredoc_signal.c \
	shell_signal.c \
	terminal_option.c 

WILD_CARD_SRCS = wild_card.c \
	check_wild_card_pattern.c \
	check_is_right_wild_card_pattern.c 

HEREDOC_SRCS = get_heredoc.c

MAIN_SRC = main.c

TEST_SRCS = test.c

SRCS1 = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRCS))
SRCS2 = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS))
SRCS3 = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
SRCS4 = $(addprefix $(RUN_DIR)/,$(RUN_SRCS))
SRCS5 = $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
SRCS6 = $(addprefix $(TEST_DIR)/,$(TEST_SRCS))
SRCS7 = $(addprefix $(WILD_CARD_DIR)/,$(WILD_CARD_SRCS))
SRCS8 = $(addprefix $(HEREDOC_DIR)/,$(HEREDOC_SRCS))

MAIN_OBJ = $(MAIN_SRC:.c=.o)
BUILTIN_OBJS = $(SRCS1:.c=.o)
LEXER_OBJS = $(SRCS2:.c=.o)
PARSER_OBJS = $(SRCS3:.c=.o)
RUN_OBJS = $(SRCS4:.c=.o)
SIGNAL_OBJS = $(SRCS5:.c=.o)
TEST_OBJS = $(SRCS6:.c=.o)
WILD_CARD_OBJS = $(SRCS7:.c=.o)
HEREDOC_OBJS = $(SRCS8:.c=.o)

OBJS = $(MAIN_OBJ) $(LEXER_OBJS) $(PARSER_OBJS) $(RUN_OBJS) $(SIGNAL_OBJS) $(BUILTIN_OBJS) $(TEST_OBJS) $(WILD_CARD_OBJS) $(HEREDOC_OBJS)
# OBJS = $(SRCS:%.c=%.o)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(MAIN_SRC) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) $(SRCS7) $(SRCS8) -o $@ -lreadline -lncurses mylib/mylib.a

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