CC = cc
C_FLAGS = -Wall -Werror -Wextra
HEADER = includes
LIBFT_DIRS = srcs/libft
PRINTF_DIRS = srcs/printf
GNL_DIRS = srcs/get_next_line

LIBFT_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
ft_strcmp.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PRINTF_SRCS = ft_printf.c ft_printf_c.c ft_printf_conversions.c ft_printf_d_i.c \
ft_printf_p.c ft_printf_s.c ft_printf_u.c ft_printf_x.c ft_putnbr_base.c ft_strlen_printf.c

GNL_SRCS = get_next_line.c get_next_line_utils.c

NAME = mylib.a

all : $(NAME)

$(NAME) : libft printf gnl

libft : $(addprefix $(LIBFT_DIRS)/, $(LIBFT_SRCS:.c=.o))
printf : $(addprefix $(PRINTF_DIRS)/, $(PRINTF_SRCS:.c=.o))
gnl : $(addprefix $(GNL_DIRS)/, $(GNL_SRCS:.c=.o))

%.o : %.c
	$(CC) $(C_FLAGS) -I$(HEADER) -c -o $@ $^
	ar rcs $(NAME) $@

clean : 
	rm -rf $(addprefix $(LIBFT_DIRS)/, $(LIBFT_SRCS:.c=.o))
	rm -rf $(addprefix $(PRINTF_DIRS)/, $(PRINTF_SRCS:.c=.o))
	rm -rf $(addprefix $(GNL_DIRS)/, $(GNL_SRCS:.c=.o))

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re libft printf gnl
