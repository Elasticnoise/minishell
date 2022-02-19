# include "../minishell.h"

static void close_in_out_file(t_token *cmd)
{
	int err;

	err = 0;
	if (cmd->outfile)
		err = close(cmd->fd.out_file);
	if (cmd->infile)
		err = close(cmd->fd.in_file);
	if (err != 0)
		perror("close_in_out_file:");
}

static inline int cmd_position(int kind, t_token *cmd, int cmd_i)
{
	int middle;
	int end;

	middle = 2;
	end = 3;
	if (cmd_i > 1 && cmd->next)
		kind = middle;
	if (kind == middle && (cmd_i > 1 && cmd->next->next == NULL))
		kind = end;
	return (kind);
}

static inline void pipe_switch(int i, int kind, int *pipes, t_token *cmd, int cmd_i)
{
	int start;
	int middle;
	int end;

	start = 1;
	middle = 2;
	end = 3;
	if (cmd_i == 2)
	{
		if (kind == start && cmd->next != NULL)
			dup2(pipes[1], STDOUT);
		else if (kind == end)
			dup2(pipes[0], STDIN);
	}
	else
	{
		if (kind == start && cmd->next != NULL)
			dup2(pipes[2 * i + 1], STDOUT);
		else if (kind == middle)
		{
			dup2(pipes[2 * i - 2], STDIN);
			dup2(pipes[2 * i + 1], STDOUT);
		}
		else if (kind == end)
			dup2(pipes[2 * i - 2], STDIN);
	}
}

static void redirect(t_token *cmd) {
	int err;

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
	if (err != 0)
		perror("1redirect:");
	err = 0;
	if (cmd->outfile)
		err = dup2(cmd->fd.out_file, STDOUT);
	if (err != 0)
	{
		perror("2redirect:");
	}
}

int do_pipex(t_token **token, char **env, t_env **n_env)
{
	int i;
	int cmd_i;
	int *pipes;
	t_token *cmd;
	int kind;
	pid_t pid;

	cmd = *token;
	cmd_i = get_cmd_count(token);
	pipes = open_pipes(cmd_i);
	kind = 1;
	i = 0;
	if (cmd && cmd->next == NULL && is_builtin(cmd->cmd[0]))
		do_builtins(cmd, n_env);
	else
	{
		while (cmd != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd_i > 1)
					pipe_switch(i, kind, pipes, cmd, cmd_i);
				if (cmd->infile || cmd->outfile)
					redirect(cmd);
				close_pipes(pipes, cmd_i);
				close_in_out_file(cmd);
				if (is_builtin(cmd->cmd[0]))
					do_builtins(cmd, n_env);
				do_exec_dev(cmd, env, n_env);
			}
//		handle_heredoc(&cmd);
//		if (cmd->limiter)
//		cmd->fd.in_file = open(".tmp_file", O_RDONLY);
			kind = cmd_position(kind, cmd, cmd_i);
			cmd = cmd->next;
			i++;
		}
	}
	cmd = *token;
	close_pipes(pipes, cmd_i);
	close_in_out_file(cmd); /// ??? it doesn't close in each node | mb no need
	wait_childs(cmd_i);
	return (EXIT_SUCCESS);
}
