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

void	redirect(t_token *cmd)
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

int	do_one_builtins(int exit_stat)
{
	if (exit_stat == EXIT_SUCCESS)
	{
		g_exit_status = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	else
	{
		g_exit_status = exit_stat;
		return (EXIT_FAILURE);
	}
}

void	loop(t_token **token, char **env, t_env **n_env, int *pipes)
{
	pid_t	pid;
	t_token	*cmd;
	t_init	init;

	cmd = *token;
	init_values(&init, token);
	while (cmd != NULL)
	{
		if (!cmd->cmd)
		{
			cmd = cmd->next;
			continue ;
		}
		pid = fork();
		if (pid && !cmd->limiter)
			catch_heredog_sig();
		if (pid == 0)
		{
			set_mutiple_cmd(cmd, &init, pipes);
			do_exec_dev(cmd, env, n_env);
		}
		init.kind = cmd_position(init.kind, cmd, init.cmd_i);
		cmd = cmd->next;
		init.i++;
	}
}

int	do_pipex(t_token **token, char **env, t_env **n_env)
{
	int		cmd_i;
	int		*pipes;
	t_token	*cmd;

	cmd = *token;
	cmd_i = get_cmd_count(token);
	pipes = open_pipes(cmd_i);
	if (cmd->cmd && cmd->next == NULL && is_builtin(cmd->cmd[0]))
		do_one_builtins(do_builtins(cmd, n_env));
	else
		loop(token, env, n_env, pipes);
	final_process_work(token, pipes, cmd_i);
	return (EXIT_SUCCESS);
}
