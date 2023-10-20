# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/10/20 15:05:13 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
C_FLAGS = -I$(HEADER)
MAIN_SRC = main.c
BUILTIN_DIR = srcs/builtin_dir
ENTRY_DIR = srcs/entry_dir
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
RUN_DIR = srcs/run_dir
SIGNAL_DIR = srcs/signal_dir
TEST_DIR = srcs/test_dir

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

ENTRY_SRCS = temp_file.c \

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
	parser_utils.c \
	parser.c \
	tree_node_utils.c \
	
RUN_SRCS = get_path.c \
	path_utils.c \
	run_command.c \
	run_exe.c \
	run_fork.c \
	run_redir.c \
	run_root.c \
	run_utils.c

SIGNAL_SRCS = blocking_signal.c \
	heredoc_signal.c \
	shell_signal.c \
	terminal_option.c \

RUN_SRCS = init_path_env-1.c \
	main.c \
	path.c \
	run_command.c \
	run_exe.c \
	run_fork.c \
	run_redir.c \
	run_root.c \
	run_utils.c

TEST_SRCS = test.c

SRCS1 = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRCS))
SRCS2 = $(addprefix $(ENTRY_DIR)/,$(ENTRY_SRCS))
SRCS3 = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS))
SRCS4 = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
SRCS5 = $(addprefix $(RUN_DIR)/,$(RUN_SRCS))
SRCS6 = $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
SRCS7 = $(addprefix $(TEST_DIR)/,$(TEST_SRCS))

MAIN_OBJ = $(MAIN_SRC:.c=.o)
BUILTIN_OBJS = $(SRCS1:.c=.o)
ENTRY_OBJS = $(SRCS2:.c=.o)
LEXER_OBJS = $(SRCS3:.c=.o)
PARSER_OBJS = $(SRCS4:.c=.o)
RUN_OBJS = $(SRCS5:.c=.o)
SIGNAL_OBJS = $(SRCS6:.c=.o)
TEST_OBJS = $(SRCS7:.c=.o)

OBJS = $(MAIN_OBJ) $(BUILTIN_OBJS) $(ENTRY_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(RUN_OBJS) $(SIGNAL_OBJS) $(TEST_OBJS)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(MAIN_SRC) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) $(SRCS7) -o $@ -lreadline -lncurses mylib/mylib.a

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