/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:01:10 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 17:01:11 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	get_cmd_count(t_token **token)
{
	int		i;
	t_token	*cmd;

	i = 0;
	cmd = *token;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	close_pipes(int *pipes, int count_node)
{
	int	i;
	int	n;

	i = 0;
	n = 2 * (count_node - 1);
	while (i < n)
		close(pipes[i++]);
}

int	*open_pipes(int cmd_i)
{
	int	i;
	int	*pipes;

	pipes = ft_calloc(sizeof(int), 2 * (cmd_i - 1));
	if (!(pipes))
		perror("open_pipes: can't malloc");
	i = 0;
	while (i < (cmd_i - 1))
	{
		if (pipe(pipes + 2 * i) == -1)
			perror("open_pipes: can't open pipe");
		i++;
	}
	return (pipes);
}

void	wait_childs(int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		wait(&status);
		if (WIFEXITED(status) && status != 0)
			signal_exit_status = 127;
		i++;
	}
}
