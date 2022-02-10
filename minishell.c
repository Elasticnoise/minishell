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

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	int 	status;
	t_main	main;
	t_token *token;
	(void)	argv;
	(void)	argc;
	(void)	(env);
	if (argc != 1)
		return (1);

	status = 1;

	while(1)
	{
//		ft_putstr_fd("sh> ", 1);
//		get_next_line(1 , &line);
		line = readline(BEGIN(49, 34)"Shkad $ "CLOSE);
		if (line && *line)
			add_history(line);
		parser(line, &token, env);
//		printf("%s\n", token->cmd);
//		ft_exit(&token);
//		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало cntrl + d
//		free(line);
//		free_list(token);
//		status = executor(&token, env);
//		printf("|%c| 000000 CHAR\n",token->str[0]);
//		if (token->str[0] != ' ')
			executor(&token, env);
//		printf("1111!!!!!!!!!\n");
		free_list(&token);
	}
	return (0);
}