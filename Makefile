# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 16:27:04 by sejkim2           #+#    #+#              #
#    Updated: 2023/08/25 12:46:08 by sejkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
C_FLAGS = -Wall -Werror -Wextra

SRCS = srcs/test.c 

SRCS_BONUS = 

NAME = a.out

ifdef BONUS
	SRC = $(SRCS_BONUS)
	OBJ = $(SRCS_BONUS:%.c=%.o)
	HEADER = includes/pipex_bonus.h
else
	SRC = $(SRCS)
	OBJ = $(SRCS:%.c=%.o)
	HEADER = includes/minishell.h
endif

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
# make -C ./mylib
	$(CC) $(C_FLAGS) $(SRC) -o $@ -L /Users/sejkim2/.brew/opt/readline/lib -lreadline -lncurses

bonus:
	make BONUS=1

clean :
# make clean -C ./mylib
	rm -rf $(SRCS:%.c=%.o) $(SRCS_BONUS:%.c=%.o)

fclean : clean
# make fclean -C ./mylib
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re