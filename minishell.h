/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:13:18 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 18:13:20 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include "/Users/lechalme/.brew/Cellar/readline/8.1.2/include/readline/readline.h"
# include "/Users/lechalme/.brew/Cellar/readline/8.1.2/include/readline/history.h"
# define STDIN	0
# define STDOUT	1

int	signal_exit_status;

struct termios termios_save;

typedef struct s_fd
{
	int	in_file;
	int	out_file;
}				t_fd;

typedef struct s_token
{
	char			**cmd;
	char			*str;
	char			*infile;
	char			*outfile;
	char			*limiter;
	struct s_token	*next;
	struct s_token	*prev;
	t_fd			fd;
}		t_token;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}t_env;

typedef struct s_main
{
	t_token	*head;
}t_main;

/*PIPE*/
int		do_pipex(t_token **token, char **env, t_env **n_env);
char	*get_path(char **envp, char *cmd);
void	do_exec_dev(t_token *token, char **envp);
int		get_cmd_count(t_token **token);
void	close_pipes(int *pipes, int count_node);
int		*open_pipes(int cmd_i);
void	wait_childs(int n);

/*BUILTINS*/
int		do_builtins(t_token *token, t_env **n_env);
int		is_builtin(char *cmd);
int		ft_exit(t_token *token, t_env **n_env);
int		ft_check_exit_status(char *str);
int		ft_exit_status(char *str);
void	ft_exit_err_msg(char *str);
int		check_exit_status(t_env **env);
int		ft_cd(t_token *token, t_env *n_env);
int		ft_env(t_env **n_env);
int		ft_unset(t_token *cmd, t_env **env);
int		ft_export(t_token *token, t_env **env);
int		ft_pwd(t_token *token);
int		ft_echo(t_token *token);
int		check_var(char *key, t_token *token);
int		ft_set_var(t_token *token, t_env *n_env, char *key, char *value);
/*SIGNALS*/
void	sig_handler(int signum);
void	sig_handler2(int signum);
void	sig_handler3(int signum);
int		lvl_down(t_env **start);
void	handle_heredoc(t_token **cmd);
void	set_exit_status(int cmd_i);

int		parser(char *line, t_token **token, char *env[], t_env **n_env);
int		quotes(char *line, int i);
char	**ft_q_split(char *s, char c);
int		check_delimiter(char c);
int		get_shlvl(t_env **n_env);

/*Dollar_set*/
void	set_dollar(char **str, int start, t_env **env);
char	**list_to_env(t_env **start);
void	free_doublechar(char **new_env);

void	set_one_node(char *str, t_env **n_env);
void	delete_quotes(char **string, t_env **env);
int		new_quotes(char *str, int j);
#endif
