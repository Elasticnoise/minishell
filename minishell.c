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

void	free_list(t_token **head)
{
	t_token	*tmp;
	int		i;

	while (*head)
	{
		i = 0;
		tmp = (*head)->next;
		if ((*head)->infile)
			free((*head)->infile);
		if ((*head)->outfile)
			free((*head)->outfile);
		if ((*head)->limiter)
			free((*head)->limiter);
		if ((*head)->cmd)
		{
			while ((*head)->cmd[i])
			{
				free((*head)->cmd[i]);
				i++;
			}
			free((*head)->cmd);
		}
		free(*head);
		*head = tmp;
	}
}

void	do_exec_dev(t_token *token, char **envp, t_env **n_env)
{
	if (is_builtin(token->cmd[0]))
		exit (do_builtins(token, n_env));
	signal(SIGQUIT, SIG_DFL);
	if ((execve(get_path(envp, token->cmd[0]), token->cmd, envp) == -1))
	{
		ft_putstr_fd("Shkad: ", 2);
		ft_putstr_fd(token->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		g_exit_status = 127;
	}
	exit(127);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_token			*token;
	char			**new_env;
	t_env			*n_env;

	if (argc != 1)
		return (1);
	g_exit_status = 0;
	n_env = NULL;
	set_env(env, &n_env);
	lvl_up(&n_env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		new_env = list_to_env(&n_env);
		signal(SIGINT, &sig_handler);
		line = readline("\x1b[35mShkad $\x1b[0m ");
		signal(SIGINT, &sig_handler2);
		if (line && *line)
			add_history(line);
		if (line)
		{
			if (ft_strcmp(line, ""))
			{
				if (!parser(line, &token, &n_env))
					do_pipex(&token, new_env, &n_env);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			free_list(&token);
			exit(EXIT_SUCCESS);
		}
		free_doublechar(new_env);
		unlink(".tmp_file");
		free_list(&token);
		if (check_exit_status(&n_env))
			exit(g_exit_status);
	}
}