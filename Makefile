# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/08/25 16:37:39 by jaehyji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
C_FLAGS = -Wall -Werror -Wextra
LIBFTDIR = ./mylib/mylib.a
SRCS = srcs/main.c	\

OBJS = $(SRCS:%.c=%.o)
HEADER = includes/minishell.h


%.o : %.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@make -C ./mylib
	$(CC) $(C_FLAGS) $(SRCS) -o $@ mylib/mylib.a -L ./readline/lib -lreadline -lncurses

all : $(NAME)

clean :
	@make clean -C ./mylib
	rm -rf $(SRCS:%.c=%.o)

fclean : clean
	@make fclean -C ./mylib
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re