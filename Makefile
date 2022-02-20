LIBFT = ./libft/libft.a

CFLAGS = -ggdb3 -I../../.brew/opt/readline/include  -I./ #-Wall -Werror -Wextra
NAME = minishell

NAME_B = minishell_bonus

SRC = minishell.c ./parser/parser.c ./parser/quotes_split.c\
					our_builtins/builtins.c \
					our_builtins/ft_exit.c \
					our_builtins/ft_echo.c \
					our_builtins/ft_unset.c \
					our_builtins/ft_export.c \
                    pipex_bonus_part/src/get_path.c \
                    src/signals.c \
                    src/pipex.c \
                    src/pipex_utils.c \
                    ./src/dollar/dollar_set.c \
                    ./parser/delete_quotes.c \


CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) -lreadline -L ../../.brew/opt/readline/lib -o $(NAME) $(OBJ) ./libft/libft.a

%.o: %.c
		gcc $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re