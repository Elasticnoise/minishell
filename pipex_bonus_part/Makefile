LIBFT = ../libft/libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I ./

NAME = pipex

SRC = pipex.c \
						includes/get_path.c \

LIB = ar -rcs $(NAME)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ../libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ../libft/libft.a

%.o: %.c
		gcc -I./ -c $< -o $@

clean:
		$(MAKE) clean -C ../libft
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) fclean -C ../libft
		rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re