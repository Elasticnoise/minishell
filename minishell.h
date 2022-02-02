//
// Created by Leota Chalmers on 12/25/21.
//
#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "lexer.h"
# include <readline/readline.h>

# define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
# define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным
# define STDIN	0
# define STDOUT	1
# define INFILE	0
# define	OUTFILE	1
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

//enum e_TokenType{
//	PARSE,
//	CMD,
//	ARV,
//	PIPE,
//	GREATER,
//	LESSER,
//	T_GREATER,
//	T_LESSER
//};

typedef struct s_fd
{
	int in_file;
	int out_file;
}				t_fd;

typedef struct s_token
{
	char	*str;
	int 	count_cmd;
	char 	*infile;
	char	*outfile;
	void			*content;
	enum	e_TokenType type;
	struct s_token *next;
	struct s_token *prev;
	t_fd	fd;
}		t_token;

typedef struct s_main
{
	t_token *head;
}t_main;

//typedef struct s_list
//{
//	char			*cmd;
//	char			**argv;
//	struct	s_list	*next;
//}				t_list;

#endif

/*PIPE*/
int		ft_redirect(char **av, char **env, int in_file, int out_file, int i);
void	do_exec(char **av, char **envp, int i);
void	set_in_out_files(t_token *token);
char	*get_path(char **envp, char *cmd);
int	ft_redirect_dev(t_token *token, char **env);
void	do_exec_dev(t_token *token, char **envp);

/*BUILTINS*/
int 	ft_exit(t_main *token);
int 	ft_cd(char **env);
void 	ft_env(t_main *main);
int 	ft_unset(char **env);
int 	ft_export(char **env);
int 	ft_pwd(t_main *main);
int 	ft_echo(t_main *main);
int 	is_builtin(t_main *main);
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