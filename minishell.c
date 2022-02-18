/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:41:55 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/25 19:41:57 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list(t_token **head)
{
	t_token *tmp;
	int		i;

//	tmp = *head;
	while (*head)
	{
		i = 0;
		tmp = (*head)->next;
		while ((*head)->cmd[i])
		{
			free((*head)->cmd[i]);
			i++;
		}
		if ((*head)->cmd)
			free((*head)->cmd);
		free((*head)->str); //todo Split free
		free(*head);
		*head = tmp;
	}
}


void	set_in_out_files(t_token *token)
{
	if (token->infile)
		token->fd.in_file = open(token->infile, O_RDONLY);
	else
		token->fd.in_file = 0;
	if (token->outfile)
		token->fd.out_file = open(token->outfile, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
	else
		token->fd.out_file = 1;
	if (token->fd.in_file < 0)
	{
		ft_putstr_fd("cat: ", 2);
		ft_putstr_fd(token->infile, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

/*TODO need to change char **envp to t_env *envp*/
void	do_exec_dev(t_token *token, char **envp, t_env **n_env)
{
//	if (is_builtin(token->cmd[0]))
//		do_builtins(token, envp, n_env);
//	else
//	{
		if ((execve(get_path(envp, token->cmd[0]), token->cmd, envp) == -1))
		{
//			int i = 0;
//			while (token->cmd[i])
//			{
//				printf("%s --- FROM EXECVE\n", token->cmd[i]);
//				i++;
//			}
			printf("Shkad: %s: command not found\n", token->cmd[0]);
			exit(127);
		}
//	}
}

int	ft_redirect_dev(t_token *token, char **env, t_env **n_env, int *help[],
					   int i)
{
	int		pid;
	pid_t	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	(*help)[i] = pid;
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (1);
	}
	if (pid == 0)
	{
//		close(pipe_fd[1]);
		close(pipe_fd[0]);
		if (!token->infile)
			dup2(pipe_fd[0], STDIN);
		else
		{
//			printf("213\n");
			dup2(token->fd.in_file, STDIN);
//			close(pipe_fd[0]);
		}
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
		do_exec_dev(token, env, n_env);
	}
	else
	{
		if (!token->outfile)
			dup2(pipe_fd[1], STDOUT);
		else
		{
//			close(pipe_fd[1]);
			dup2(token->fd.out_file, STDOUT);
		}
		close(pipe_fd[1]);
//		printf("kek");
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		close(pipe_fd[1]); ////
//		dup2(token->fd.in_file, STDIN); ///
//		waitpid(pid, NULL, 0);
	}
	return (0);
}

void	handle_heredoc(t_token **cmd)
{
	int 	limiter;
	int		fd;
	char 	*line;

	if ((*cmd)->limiter)
	{
		fd = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		while (1)
		{
			line = readline("> ");
			limiter = ft_strncmp(line, (*cmd)->limiter, ft_strlen((*cmd)->limiter) + 1);
			if (limiter == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		free(line);
		(*cmd)->fd.in_file = fd;
		close(fd);
	}
}

int	executor(t_token **token, char **env, t_env **n_env)
{
	t_token	*cmd;
	pid_t	pid;

	cmd = *token;
	if (cmd && cmd->next == NULL && is_builtin(cmd->cmd[0]))
		do_builtins(cmd, env, n_env);
	else if ( cmd && !(cmd->next))
	{
		pid = fork();
//		int fd[2];
//		pipe(fd);
		if (pid == 0)
		{
//			handle_heredoc(&cmd);
//			if (cmd->limiter)
//				cmd->fd.in_file = open(".tmp_file", O_RDONLY);
			dup2(cmd->fd.in_file, INFILE);
			if (cmd->outfile)
				dup2(cmd->fd.out_file, OUTFILE);
//			waitpid(pid, NULL, 0);
			do_exec_dev(cmd, env, n_env);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
//		cmd = *token;
//		pid = fork();
//		if (pid == 0)
//		{
//			signal(SIGINT, &sig_handler);
			if (cmd)
			{
				int *help;
				int i = 0;
				help = ft_calloc(sizeof (int) * 2, 1);
//				handle_heredoc(&cmd);
//				if (cmd->limiter)
//					cmd->fd.in_file = open(".tmp_file", O_RDONLY);
				dup2(cmd->fd.in_file, INFILE);
				while (cmd)
				{
					ft_redirect_dev(cmd, env, n_env, &help, i);
					cmd = cmd->next;
					i++;
				}
//				i--;
//				while (i >= 0)
//				{
//					waitpid(help[i], NULL, i);
//					i--;
//				}
//				if (cmd->outfile)
//					dup2(cmd->fd.out_file, OUTFILE);
//				waitpid(pid, NULL, 0);
//				do_exec_dev(cmd, env, n_env);
//				waitpid(pid, NULL, 0);
			}
//			else
//				waitpid(pid, NULL, 0);
//		}
//		else
//		{
//			signal(SIGINT, &sig_handler);
//			waitpid(pid, NULL, 0);
//		}
	}
	return (1);
}


t_env	*new_env(char *name, char *data)
{
	t_env	*n_env;

	n_env = malloc(sizeof(t_env));
	if (!n_env)
		return (NULL);
	n_env->name = name;
	n_env->data = data;
	n_env->next = NULL;
	return (n_env);
}

void add_env(t_env	**start, t_env *new)
{
	t_env *tmp;

	tmp = *start;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*start = new;
}


void	set_one_node(char *str, t_env **n_env)
{
	int start;
	int j;
	char *name;
	char *data;

	start = 0;
	j = 0;
	name = NULL;
	while (str[j])
	{
		if (start == 0 && str[j] == '=')
		{
			name = ft_substr(str, 0, j);
			start = j + 1;
		}
		j++;
	}
	if (name == NULL)
	{
		name = ft_substr(str, 0, j);
		start = j + 1;
	}
	data = ft_substr(str, start, j);
	add_env(&(*n_env), new_env(name, data));
}

void	set_env(char **env, t_env **n_env) ////todo malloc check
{
	int		i;

	i = 0;
	while (env[i])
	{
		set_one_node(env[i], &(*n_env));
		i++;
	}
}

void print_env(t_env **start)
{
	t_env *help;

	help = *start;
	while (help)
	{
		printf("%s=%s\n", help->name, help->data);
		help=help->next;
	}
}

char **list_to_env(t_env **start)
{
	t_env *help;
	char **new_env;
	char *tmp;
	int i;
	int j;

	j = 0;
	help = *start;
	while (help)
	{
		help = help->next;
		j++;
	}
	help = *start;
	new_env = malloc(sizeof(char *) * j + 1); //todo malloc check
	i = 0;
	while (i < j)
	{
		tmp = ft_strjoin(help->name, "=");
		new_env[i] = ft_strjoin(tmp, help->data);
		i++;
		free(tmp);
		help = help->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

void lvl_up(t_env **start)
{
	t_env	*tmp;
	int		lvl;

	tmp = *start;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			lvl++;
			free(tmp->data);
			tmp->data = ft_itoa(lvl);
			break;
		}
		tmp = tmp->next;
	}
}

int	lvl_down(t_env **start)
{
	t_env	*tmp;
	int		lvl;

	tmp = *start;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			lvl--;
			free(tmp->data);
			tmp->data = ft_itoa(lvl);
			break;
		}
		tmp = tmp->next;
	}
	return (lvl);
}


#include <termios.h>
#include <unistd.h>
#include <signal.h>

struct termios termios_save;

void reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	int 	status;
	t_main	main;
	t_token *token;
	char **new_env;
	(void)	argv;
	(void)	argc;
	(void)	(env);
	t_env	*n_env;
	if (argc != 1)
		return (1);

	signal_exit_status = 0;


//	struct termios termios_new;
	int rc;
	rc = tcgetattr(0, &termios_save );
//	if (rc) {perror("tcgetattr"); exit(1); }
	rc = atexit(reset_the_terminal);
//	if (rc) {perror("atexit"); exit(1); }
//	termios_new = termios_save;
	termios_save.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_save );
//	signal(SIGQUIT, SIG_IGN);
	n_env = NULL;
	set_env(env, &n_env);
	lvl_up(&n_env);
	while(1)
	{
		signal(SIGINT, &sig_handler);
		new_env = list_to_env(&n_env);
		line = readline("\x1b[35mShkad $\x1b[0m ");
		if (line && *line)
			add_history(line);
		if (line)
		{
			if (ft_strcmp(line, ""))
			{
				parser(line, &token, env, &n_env);
				executor(&token, new_env, &n_env);
			}
		}
		else
			exit(0);
		free_doublechar(new_env);
		unlink(".tmp_file");
		free_list(&token);
		if (check_exit_status(&n_env))
			exit(signal_exit_status);
	}
}