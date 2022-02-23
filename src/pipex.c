/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:59:32 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 21:59:36 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	close_in_out_file(t_token *cmd)
{
	int	err;

	err = 0;
	if (cmd->outfile)
		err = close(cmd->fd.out_file);
	if (cmd->infile)
		err = close(cmd->fd.in_file);
	if (err != 0)
		perror("close_in_out_file:");
}

static inline int	cmd_position(int kind, t_token *cmd, int cmd_i)
{
	int	middle;
	int	end;

	middle = 2;
	end = 3;
	if (cmd_i > 1 && cmd->next)
		kind = middle;
	if (kind == middle && (cmd_i > 1 && cmd->next->next == NULL))
		kind = end;
	return (kind);
}

static inline void	pipe_switch(int i, int kind, int *pipes, t_token *cmd, int cmd_i)
{
	if (cmd_i == 2)
	{
		if (kind == START && cmd->next != NULL)
			dup2(pipes[1], STDOUT);
		else if (kind == END)
			dup2(pipes[0], STDIN);
	}
	else
	{
		if (kind == START && cmd->next != NULL)
			dup2(pipes[2 * i + 1], STDOUT);
		else if (kind == MIDDLE)
		{
			dup2(pipes[2 * i - 2], STDIN);
			dup2(pipes[2 * i + 1], STDOUT);
		}
		else if (kind == END)
			dup2(pipes[2 * i - 2], STDIN);
	}
}

static void	redirect(t_token *cmd)
{
	int	err;

	err = 0;
	if (cmd->infile)
	{
		if (cmd->limiter)
		{
			handle_heredoc(&cmd);
			cmd->fd.in_file = open(".tmp_file", O_RDONLY);
		}
		err = dup2(cmd->fd.in_file, STDIN);
	}
	if (err == -1)
		perror("1redirect:");
	err = 0;
	if (cmd->outfile)
		err = dup2(cmd->fd.out_file, STDOUT);
	if (err == -1)
	{
		perror("2redirect:");
	}
}

void	do_child(t_token *cmd, int cmd_i, int *pipes, int i, int kind)
{
	handle_heredoc(&cmd);
	if (cmd->limiter)
		cmd->fd.in_file = open(".tmp_file", O_RDONLY);
	if (cmd_i > 1)
		pipe_switch(i, kind, pipes, cmd, cmd_i);
	if (cmd->infile || cmd->outfile)
		redirect(cmd);
	close_pipes(pipes, cmd_i);
	close_in_out_file(cmd);
}

int	do_one_builtins(int exit_stat, int *pipes)
{
	if (exit_stat == EXIT_SUCCESS)
	{
		g_exit_status = EXIT_SUCCESS;
		free(pipes);
		return (EXIT_SUCCESS);
	}
	else
	{
		g_exit_status = exit_stat;
		free(pipes);
		return (EXIT_FAILURE);
	}
}

int	do_pipex(t_token **token, char **env, t_env **n_env)
{
	int		i;
	int		cmd_i;
	int		*pipes;
	t_token	*cmd;
	int		kind;
	pid_t	pid;
	int		exit_stat;

	cmd = *token;
	cmd_i = get_cmd_count(token);
	pipes = open_pipes(cmd_i);
	kind = 1;
	i = 0;
	if (cmd->cmd && cmd->next == NULL && is_builtin(cmd->cmd[0]))
	{
		exit_stat = do_builtins(cmd, n_env);
		do_one_builtins(exit_stat, pipes);
	}
	else
	{
		while (cmd != NULL)
		{
			if (!cmd->cmd)
			{
				cmd = cmd->next;
				continue ;
			}
			pid = fork();
			if (pid && !cmd->limiter)
			{
				signal(SIGINT, sig_handler3);
				signal(SIGQUIT, sig_handler3);
			}
			if (pid == 0)
			{
				do_child(cmd, cmd_i, pipes, i, kind);
				if (is_builtin(cmd->cmd[0]))
					exit (do_builtins(cmd, n_env));
				do_exec_dev(cmd, env);
			}
			kind = cmd_position(kind, cmd, cmd_i);
			cmd = cmd->next;
			i++;
		}
	}
	cmd = *token;
	close_pipes(pipes, cmd_i);
	close_in_out_file(cmd);
	set_exit_status(cmd_i);
	wait_childs(cmd_i);
	if (pipes)
		free(pipes);
	return (EXIT_SUCCESS);
}
