LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -I./

NAME = minishell

NAME_B = minishell_bonus

SRC = minishell.c \


LIB = ar -rcs $(NAME)

OBJ = $(SRC:.c=.o)

all: $(NAME)
## TODO need to add Flags
$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) -lreadline -o $(NAME) $(OBJ) ./libft/libft.a

#$(NAME1): $(OBJ1)
#		$(MAKE) -C ./libft
#		$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ1) ./libft/libft.a

%.o: %.c
		gcc -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re