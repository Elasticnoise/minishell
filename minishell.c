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

void	do_exec_dev(t_token *token, char **envp, t_env **n_env)
{
	if (is_builtin(token->cmd[0]))
		exit (do_builtins(token, n_env, envp));
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

void	go_exit(t_token **token)
{
	ft_putstr_fd("exit\n", 1);
	free_list(token);
	exit(EXIT_SUCCESS);
}

void	play_command(char *line, t_token **token, t_env **n_env, char **new_env)
{
	if (!parser(line, token, n_env))
		do_pipex(token, new_env, n_env);
}

void	ft_shell(t_token **token, t_env **n_env, char *line, char **new_env)
{
	if (line)
	{
		if (ft_strcmp(line, ""))
			play_command(line, token, n_env, new_env);
		else
			free(line);
	}
	else
		go_exit(token);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;
	char	**new_env;
	t_env	*n_env;
	int		help;

	g_exit_status = 0;
	n_env = NULL;
	set_env(env, &n_env, &help);
	lvl_up(&n_env, argv, argc);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		new_env = list_to_env(&n_env);
		signal(SIGINT, &sig_handler);
		line = readline("\x1b[35mShkad $\x1b[0m ");
		signal(SIGINT, &sig_handler2);
		if (line && *line)
			add_history(line);
		ft_shell(&token, &n_env, line, new_env);
		ft_clean(&token, new_env, &n_env, help);
	}
}
