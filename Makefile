LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -I./

NAME = minishell

NAME_B = minishell_bonus

SRC = minishell.c \



SRC_BONUS =

LIB = ar -rcs $(NAME)

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_BONUS:.c=.o)

all: $(NAME) $(NAME1)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ./libft/libft.a

$(NAME1): $(OBJ1)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ1) ./libft/libft.a

%.o: %.c
		gcc $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJ)
		rm -rf $(OBJ_B)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)
		rm -rf $(NAME_B)
re: fclean all

.PHONY:	all clean fclean re