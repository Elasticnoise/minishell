LIBFT = ./libft/libft.a

CFLAGS = -ggdb3 -I../../.brew/opt/readline/include  -I./ -Wall -Werror -Wextra
NAME = minishell

NAME_B = minishell_bonus

SRC = minishell.c ./parser/parser.c ./parser/quotes_split.c\
					our_builtins/builtins.c \
					our_builtins/builtins_utils.c \
					our_builtins/ft_exit.c \
					our_builtins/ft_exit_utils.c \
					our_builtins/ft_echo.c \
					our_builtins/here_doc.c \
					our_builtins/ft_unset.c \
					our_builtins/ft_export.c \
					our_builtins/ft_cd.c \
                    src/signals.c \
                    src/clean.c \
                    src/get_path.c \
                    src/pipex_utils2.c \
                    src/pipex.c \
                    src/pipex_utils.c \
                    ./src/dollar/dollar_set.c \
                    ./parser/delete_quotes.c \
                    ./src/dollar/find_env_node.c \
                    ./parser/new_token.c \
                    ./parser/parser_utils.c \
                    ./src/env_func.c \
                    ./src/env_func_2.c \


CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@stty -ctlecho
		@$(MAKE) -C ./libft
		@$(CC) -lreadline -L ../../.brew/opt/readline/lib -o $(NAME) $(OBJ) ./libft/libft.a
		@echo "\x1b[7m\x1b[47m\x1b[31m\
\x1b[7m\x1b[47m\x1b[31m╭━━━┳╮\x1b[30m╱\x1b[31m╭╮\x1b[30m╱╱╱╱╱╱\x1b[31m╭╮\x1b[35m╭━━━╮\x1b[30m╱╱╱╱╱╱╱╱╱╱\x1b[35m╭╮\x1b[31m╭━━━┳╮\x1b[30m╱\x1b[31m╭┳━━━┳╮\x1b[30m╱╱\x1b[31m╭╮\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[31m┃╭━╮┃┃\x1b[30m╱\x1b[31m┃┃\x1b[30m╱╱╱╱╱╱\x1b[31m┃┃\x1b[35m┃╭━╮┃\x1b[30m╱╱╱╱╱╱╱╱╱╱\x1b[35m┃┃\x1b[31m┃╭━╮┃┃\x1b[30m╱\x1b[31m┃┃╭━━┫┃\x1b[30m╱╱\x1b[31m┃┃\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[31m┃╰━━┫╰━┫┃╭┳━━┳━╯┃\x1b[35m┃╰━━┳━━┳╮╭┳━━┳━╯┃\x1b[31m┃╰━━┫╰━╯┃╰━━┫┃\x1b[30m╱╱\x1b[31m┃┃\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[31m╰━━╮┃╭╮┃╰╯┫╭╮┃╭╮┃\x1b[35m╰━━╮┃╭╮┃┃┃┃╭╮┃╭╮┃\x1b[31m╰━━╮┃╭━╮┃╭━━┫┃\x1b[30m╱\x1b[31m╭┫┃\x1b[30m╱\x1b[31m╭╮\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[31m┃╰━╯┃┃┃┃╭╮┫╭╮┃╰╯┃\x1b[35m┃╰━╯┃╰╯┃╰╯┃╭╮┃╰╯┃\x1b[31m┃╰━╯┃┃\x1b[30m╱\x1b[31m┃┃╰━━┫╰━╯┃╰━╯┃\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[31m╰━━━┻╯╰┻╯╰┻╯╰┻━━╯\x1b[35m╰━━━┻━╮┣━━┻╯╰┻━━╯\x1b[31m╰━━━┻╯\x1b[30m╱\x1b[31m╰┻━━━┻━━━┻━━━╯\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[30m╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱\x1b[35m┃┃\x1b[0m\n\
\x1b[7m\x1b[47m\x1b[30m╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱\x1b[35m╰╯\x1b[30m\\\\\x1b[35m is ready\x1b[0m"

%.o: %.c
		@gcc $(CFLAGS) -c $< -o $@

clean:
		@$(MAKE) clean -C ./libft
		@rm -rf $(OBJ)

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -rf $(NAME)
re: fclean all

.PHONY:	all clean fclean re