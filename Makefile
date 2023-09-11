# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/09/07 20:03:12 by jaehyji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# C_FLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c	\
	srcs/lexer.c \
	srcs/check_character_type.c \
	srcs/node.c \
	srcs/list.c \
	srcs/tokenize.c \
	srcs/free_list.c \
	srcs/shell_signal.c	\
	srcs/blocking_signal.c \
	srcs/heredoc_signal.c	\
	srcs/terminal_option.c	\

OBJS = $(SRCS:%.c=%.o)
HEADER = includes/minishell.h


%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
# @make -C ./mylib
# $(CC) $(C_FLAGS) $(SRCS) -o $@ -L ./readline/lib -lreadline -lncurses
	$(CC) $(C_FLAGS) $(SRCS) -o $@ -lreadline -lncurses

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