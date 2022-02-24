/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:19:04 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/24 15:19:12 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	set_mutiple_cmd(t_token *cmd, int cmd_i, int *pipes, int i, int kind)
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

void	final_process_work(t_token **token, int *pipes, int cmd_i)
{
	t_token	*cmd;

	cmd = *token;
	close_pipes(pipes, cmd_i);
	close_in_out_file(cmd);
	set_exit_status(cmd_i);
	wait_childs(cmd_i);
	if (pipes)
		free(pipes);
}

void	pipe_switch(int i, int kind, int *pipes, t_token *cmd, int cmd_i)
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

void	close_in_out_file(t_token *cmd)
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
