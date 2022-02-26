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
# include "/Users/ghanh/.brew/Cellar/readline/8.1.2/include/readline/readline.h"
# include "/Users/ghanh/.brew/Cellar/readline/8.1.2/include/readline/history.h"
# define STDIN	0
# define STDOUT	1
# define START	1
# define MIDDLE	2
# define END	3

int	g_exit_status;

typedef struct s_fd
{
	int	in_file;
	int	out_file;
}				t_fd;

typedef struct s_init
{
	int	cmd_i;
	int	kind;
	int	i;
}				t_init;

typedef struct s_token
{
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*limiter;
	struct s_token	*next;
	t_fd			fd;
}		t_token;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}t_env;

/*PIPE*/
int		do_pipex(t_token **token, char **env, t_env **n_env);
char	*get_path(char **envp, char *cmd);
void	do_exec_dev(t_token *token, char **envp, t_env **n_env);
int		get_cmd_count(t_token **token);
void	close_pipes(int *pipes, int count_node);
int		*open_pipes(int cmd_i);
void	wait_childs(int n);
void	set_mutiple_cmd(t_token *cmd, t_init *init, int *pipes);
void	pipe_switch(int *pipes, t_token *cmd, t_init *init);
void	redirect(t_token *cmd);
void	close_in_out_file(t_token *cmd);
void	final_process_work(t_token **token, int *pipes, int cmd_i);
void	init_values(t_init *init, t_token **token);
void	ft_clean(t_token **token, char	**new_env, t_env **n_env, int help);
void	free_list(t_token **head);

/*BUILTINS*/
int		do_builtins(t_token *token, t_env **n_env, char **env);
int		is_builtin(char *cmd);
int		ft_exit(t_token *token, t_env **n_env);
int		ft_check_exit_status(char *str);
int		ft_exit_status(char *str);
void	ft_exit_err_msg(char *str);
int		check_exit_status(t_env **env, int help);
int		ft_cd(t_token *token, t_env **n_env);
int		ft_env(t_env **n_env);
int		ft_unset(t_token *cmd, t_env **env);
int		ft_export(t_token *token, t_env **env);
int		ft_pwd(t_token *token);
int		ft_echo(t_token *token);
int		check_var(char *key, t_token *token);
int		ft_set_var(t_token *token, t_env **n_env, char *key, char *value);
void	handle_heredoc(t_token **cmd);
int		ft_shkad(t_token *token, char **envp);
/*SIGNALS*/
void	sig_handler(int signum);
void	sig_handler2(int signum);
void	sig_handler3(int signum);
int		lvl_down(t_env **start);
void	lvl_up(t_env **start, char **argv, int argc);
void	set_exit_status(void);
void	catch_heredog_sig(void);

void	add_env(t_env	**start, t_env *new);
int		parser(char *line, t_token **token, t_env **n_env);
int		quotes(char *line, int i);
char	**ft_q_split(char *s, char c);
int		check_delimiter(char c);
int		get_shlvl(t_env **n_env);

/*Dollar_set*/
void	set_env(char **env, t_env **n_env, int *help);
void	set_dollar(char **str, int start, t_env **env);
char	**list_to_env(t_env **start);
void	free_doublechar(char **new_env);
t_env	*new_env(char *name, char *data);
void	set_one_node(char *str, t_env **n_env);
void	delete_quotes(char **string, t_env **env);
int		new_quotes(char *str, int j);
t_env	*find_help(t_env **env, char *new);
t_token	*new_token(char	*str, t_env **env);
int		malloc_sp(char *line);
char	set_del(int max);
char	*destroy_space(char *line);
void	del_var(t_env **env, char *key);
void	set_var(t_env **env, char *key);
int		find_len(char *str);
#endif
