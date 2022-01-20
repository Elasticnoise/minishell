//
// Created by Leota Chalmers on 12/25/21.
//
#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include "lexer.h"
# include <readline/readline.h>

# define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
# define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным
// шрифтом, выделить
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"



enum e_TokenType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN	= -1,
};

typedef struct s_token
{
	char	*str;
	char 	*infile;
	char	*outfile;
	enum	e_TokenType type;
	struct s_token *next;
	struct s_token *prev;
}		t_token;

typedef struct s_main
{
	t_token *head;
}t_main;

#endif

//readline add_history
//
//rl_clear_history,
// rl_on_new_line, -
//rl_replace_line, rl_redisplay,

//printf, malloc, free, write, access, open, read,
//close, fork, wait, waitpid, wait3, wait4,
// signal,
//sigaction, kill, exit, getcwd, chdir
// stat, lstat, fstat, unlink, execve, dup, dup2, pipe,
//opendir, readdir, closedir, strerror, perror,
//isatty, ttyname, ttyslot, ioctl,

// getenv, tcsetattr,
//tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
//tgoto, tputs