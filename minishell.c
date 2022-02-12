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

//	tmp = *head;
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->str); //todo Split free
		free(*head);
		*head = tmp;
	}
}


char	*set_var(char *line, int i, char **env)
{
	char	*begin;
	char	*end;
	char	*var;
	char	*var_value;
	int		j;

	i++;
	j = i;
	begin = ft_substr(line, 0, i);
	while (line[j] != ' ')
		j++;
	if (j != i)
		var_value = "$";
	else
		var_value = ft_substr(env[i], ft_strlen(var) + 1,
							  ft_strlen(env[i]) - (ft_strlen(var) + 1));
	var = ft_substr(line, i, j - i);
	end = ft_substr(line, j, ft_strlen(line) - j);
	i = 0;
	while (ft_strncmp(env[i], var, ft_strlen(var)) != 0)
		i++;
	begin = ft_strjoin(begin, var_value);
	begin = ft_strjoin(begin, " ");
	begin = ft_strjoin(begin, end);
	free(end);
	printf("'%s' -- cmd\n", var_value);
//	free(var_value);
	return (begin);
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

void	do_exec_dev(t_token *token, char **envp)
{
	if (execve(get_path(envp, token->cmd[0]), token->cmd, envp) == -1)
	{
		printf("Shkad: %s: command not found\n", token->cmd[0]);
		exit(127);
	}
}

int	ft_redirect_dev(t_token *token, char **env)
{
	int		pid;
	pid_t	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (1);
	}
	if (pid)
	{
		close(pipe_fd[1]);
		if (!token->infile)
			dup2(pipe_fd[0], STDIN);
		else
			dup2(token->fd.in_file, STDIN);
	}
	else
	{
		close(pipe_fd[0]);
		if (!token->outfile)
			dup2(pipe_fd[1], STDOUT);
		else
			dup2(token->fd.out_file, STDOUT);
		do_exec_dev(token, env);
		waitpid(pid, NULL, 0);
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
		fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
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

int	executor(t_token **token, char **env)
{
	t_token	*cmd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmd = *token;
		if (cmd)
		{
			handle_heredoc(&cmd);
			if (cmd->fd.in_file)
				cmd->fd.in_file = open("tmp_file", O_RDONLY);
			dup2(cmd->fd.in_file, INFILE);
			while (cmd->next)
			{
				ft_redirect_dev(cmd, env);
				cmd = cmd->next;
			}
			if (cmd->outfile)
				dup2(cmd->fd.out_file, OUTFILE);
			do_exec_dev(cmd, env);
		}
	}
	else
		waitpid(pid, NULL, 0);
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

void	set_env(char **env, t_env **n_env) ////todo malloc check
{
	int		i;
	int 	j;
	int		start;
	char	*data;
	char 	*name;

	j = 0;
	i = 0;
	while (env[i])
	{
		start = 0;
		j = 0;
		while (env[i][j])
		{
			if (start == 0 && env[i][j] == '=')
			{
				name = ft_substr(env[i], 0, j);
				start = j + 1;
			}
			j++;
		}
		data = ft_substr(env[i], start, j);
		add_env(&(*n_env), new_env(name, data));
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
	new_env = malloc(sizeof(char *) * j); //todo malloc check
	i = 0;
	while (i < j)
	{
//		printf("%d\n", i);
		tmp = ft_strjoin(help->name, "=");
		new_env[i] = ft_strjoin(tmp, help->data);
		i++;
		free(tmp);
		help = help->next;
	}
	new_env[i] = NULL;
//	i = 0;
//	while (new_env[i])
//	{
//		printf("%s -- FROM NEW\n", new_env[i]);
//		i++;
//	}
//	printf("END\n");
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

	status = 1;

	signal(SIGQUIT, SIG_IGN);
	n_env = NULL;
	set_env(env, &n_env);
//	list_to_env(&n_env);
	lvl_up(&n_env);
//	new_env = list_to_env(&n_env);
	new_env = list_to_env(&n_env);
	while(1)
	{
//		ft_putstr_fd("sh> ", 1);
//		get_next_line(1 , &line);
//		signal(SIGINT, &sig_handler);
		line = readline(BEGIN(49, 34)"Shkad $ "CLOSE);
//		signal(SIGINT, &sig_handler2);
		if (line && *line)
			add_history(line);
		parser(line, &token, env, &n_env);
//		print_env(&n_env);
//		printf("%s\n", token->cmd);
//		ft_exit(&token);

		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало cntrl + d
//		free(line);
//		free_list(token);
//		status = executor(&token, env);
//		printf("|%c| 000000 CHAR\n",token->str[0]);
//		if (token->str[0] != ' ')
			executor(&token, new_env);
		unlink("tmp_file");
//		printf("1111!!!!!!!!!\n");
		free_list(&token);
	}
	return (0);
}