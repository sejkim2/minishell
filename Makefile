# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/10/30 20:06:40 by jaehyji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
C_FLAGS = -Wall -Werror -Wextra -I$(HEADER)
HEADER = includes
BUILTIN_DIR = srcs/builtin_dir
ENV_DIR = srcs/env_dir
HEREDOC_DIR = srcs/heredoc_dir
LEXER_DIR = srcs/lexer_dir
PARSER_DIR = srcs/parser_dir
RUN_DIR = srcs/run_dir
SIGNAL_DIR = srcs/signal_dir
WILD_CARD_DIR = srcs/wild_card_dir

BUILTIN_SRCS = builtin_cd.c \
	builtin_echo.c \
	builtin_env_utils.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export_utils.c \
	builtin_export.c \
	builtin_pwd.c \
	builtin_unset_utils.c \
	builtin_unset.c \
	builtin_utils.c \
	free_utils.c

ENV_SRCS = check_env_rule.c \
	env_utils.c \
	expand_env_utils.c \
	expand_env.c

HEREDOC_SRCS = get_heredoc.c \
	heredoc_utils.c

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

MAIN_SRC = main.c
SRCS1 = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRCS))
SRCS2 = $(addprefix $(ENV_DIR)/,$(ENV_SRCS))
SRCS3 = $(addprefix $(HEREDOC_DIR)/,$(HEREDOC_SRCS))
SRCS4 = $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS))
SRCS5 = $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
SRCS6 = $(addprefix $(RUN_DIR)/,$(RUN_SRCS))
SRCS7 = $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
SRCS8 = $(addprefix $(WILD_CARD_DIR)/,$(WILD_CARD_SRCS))

MAIN_OBJ = $(MAIN_SRC:.c=.o)
BUILTIN_OBJS = $(SRCS1:.c=.o)
ENV_OBJS = $(SRCS2:.c=.o)
HEREDOC_OBJS = $(SRCS3:.c=.o)
LEXER_OBJS = $(SRCS4:.c=.o)
PARSER_OBJS = $(SRCS5:.c=.o)
RUN_OBJS = $(SRCS6:.c=.o)
SIGNAL_OBJS = $(SRCS7:.c=.o)
WILD_CARD_OBJS = $(SRCS8:.c=.o)

OBJS = $(MAIN_OBJ) $(BUILTIN_OBJS) $(ENV_OBJS) $(HEREDOC_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(RUN_OBJS) $(SIGNAL_OBJS) $(WILD_CARD_OBJS)

%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@make -C ./mylib
	$(CC) $(C_FLAGS) $(MAIN_SRC) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) $(SRCS7) $(SRCS8) -o $@ -lreadline -lncurses mylib/mylib.a

all : $(NAME)

clean :
	@make clean -C ./mylib
	rm -rf $(OBJS)

fclean : clean
	@make fclean -C ./mylib
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re