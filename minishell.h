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
//# include <readline/readline.h>
//# include <readline/history.h>
# include "/Users/lechalme/.brew/Cellar/readline/8.1.2/include/readline/readline.h"
# include "/Users/lechalme/.brew/Cellar/readline/8.1.2/include/readline/history.h"

# define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
# define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным
# define STDIN	0
# define STDOUT	1
# define INFILE	0
# define	OUTFILE	1
// шрифтом, выделить
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"

int signal_exit_status;

typedef struct s_fd
{
	int in_file;
	int out_file;
}				t_fd;

typedef struct s_token
{
	char	**cmd; //[1] ls [2] -la [3]
	char	*str;  // >>. <<<
	char 	*infile;
	char	*outfile;
	char	*limiter;
	struct s_token *next;
	struct s_token *prev;
	t_fd	fd;
}		t_token;

typedef struct s_env
{
	char *name;
	char *data;
	struct s_env *next;
} t_env;

typedef struct s_main
{
	t_token *head;
}t_main;


#endif

/*PIPE*/
int		ft_redirect(char **av, char **env, int in_file, int out_file, int i);
void	do_exec(char **av, char **envp, int i);
void	set_in_out_files(t_token *token);
char	*get_path(char **envp, char *cmd);
int	ft_redirect_dev(t_token *token, char **env, t_env **n_env);
void	do_exec_dev(t_token *token, char **envp, t_env **n_env);

/*BUILTINS*/
void	do_builtins(t_token *token, char **env, t_env **n_env);
int 	is_builtin(char *cmd);
int 	ft_exit(t_token *token, t_env **n_env);
int 	ft_cd(char **env);
void 	ft_env(t_main *main);
int 	ft_unset(char **env);
int 	ft_export(char **env);
int 	ft_pwd(t_main *main);
int 	ft_echo(t_token *token);
int	check_exit_status(t_env **env);

/*SIGNALS*/
void	sig_handler(int signum);
void	sig_handler2(int signum);
int	lvl_down(t_env **start);
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

int parser(char *line, t_token **token, char *env[], t_env **n_env);
int	executor(t_token **token, char **env, t_env **n_env);
int quotes(char *line, int i);
char	**ft_q_split(char *s, char c);
int check_delimiter(char c);
int	get_shlvl(t_env **n_env);

/*Dollar_set*/
void	dollar_cmd(t_token **token, t_env **env);
 void dollar_infile(t_token **token, t_env **env);
void	set_dollar(char **str, int start, t_env **env);
void	dollar_outfile(t_token **token, t_env **env);