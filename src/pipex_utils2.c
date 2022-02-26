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

void	set_mutiple_cmd(t_token *cmd, t_init *init, int *pipes)
{
	handle_heredoc(&cmd);
	if (cmd->limiter)
		cmd->fd.in_file = open(".tmp_file", O_RDONLY);
	if (init->cmd_i > 1)
		pipe_switch(pipes, cmd, init);
	if (cmd->infile || cmd->outfile)
		redirect(cmd);
	close_pipes(pipes, init->cmd_i);
	close_in_out_file(cmd);
}

void	final_process_work(t_token **token, int *pipes, int cmd_i)
{
	t_token	*cmd;

	cmd = *token;
	close_pipes(pipes, cmd_i);
	close_in_out_file(cmd);
	set_exit_status();
	wait_childs(cmd_i);
	if (pipes)
		free(pipes);
}

void	pipe_switch(int *pipes, t_token *cmd, t_init *init)
{
	if (init->cmd_i == 2)
	{
		if (init->kind == START && cmd->next != NULL)
			dup2(pipes[1], STDOUT);
		else if (init->kind == END)
			dup2(pipes[0], STDIN);
	}
	else
	{
		if (init->kind == START && cmd->next != NULL)
			dup2(pipes[2 * init->i + 1], STDOUT);
		else if (init->kind == MIDDLE)
		{
			dup2(pipes[2 * init->i - 2], STDIN);
			dup2(pipes[2 * init->i + 1], STDOUT);
		}
		else if (init->kind == END)
			dup2(pipes[2 * init->i - 2], STDIN);
	}
}

void	close_in_out_file(t_token *cmd)
{
	if (cmd->outfile)
		close(cmd->fd.out_file);
	if (cmd->infile)
		close(cmd->fd.in_file);
	if (cmd->fd.in_file == -1)
	{
		ft_putstr_fd("Shkad: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (cmd->fd.out_file == -1)
	{
		ft_putstr_fd("Shkad: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}

void	init_values(t_init *init, t_token **token)
{
	init->cmd_i = get_cmd_count(token);
	init->kind = 1;
	init->i = 0;
}
