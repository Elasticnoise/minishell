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
		if ((*head)->cmd)
		{
			while ((*head)->cmd[i])
			{
				free((*head)->cmd[i]);
				i++;
			}
			free((*head)->cmd);
		}
		free((*head)->str);
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
		token->fd.out_file = open(token->outfile, O_TRUNC | O_WRONLY | \
													O_CREAT, S_IRUSR | \
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
	signal(SIGQUIT, SIG_DFL);
	if ((execve(get_path(envp, token->cmd[0]), token->cmd, envp) == -1))
	{
		ft_putstr_fd("Shkad: ", 2);
		ft_putstr_fd(token->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		signal_exit_status = 127;
	}
	exit(127);
}

void	handle_heredoc(t_token **cmd)
{
	int		limiter;
	int		fd;
	char	*line;

	if ((*cmd)->limiter)
	{
		fd = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			line = readline("> ");
			if (line == NULL)
				break ;
			limiter = ft_strncmp(line, (*cmd)->limiter, \
				ft_strlen((*cmd)->limiter) + 1);
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
//	if (WTERMSIG(signal_exit_status) == SIGINT)
//		signal_exit_status = 1;
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

void	add_env(t_env	**start, t_env *new)
{
	t_env	*tmp;

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

void	set_one_node(char *str, t_env **n_env)
{
	int		start;
	int		j;
	char	*name;
	char	*data;

	start = 0;
	j = 0;
	name = NULL;
	while (str[j])
	{
		if (start == 0 && str[j] == '=')
		{
			name = ft_substr(str, 0, j);
			start = j + 1;
		}
		j++;
	}
	if (name == NULL)
	{
		name = ft_substr(str, 0, j);
		start = j + 1;
	}
	data = ft_substr(str, start, j);
	add_env(&(*n_env), new_env(name, data));
}

void	set_env(char **env, t_env **n_env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		set_one_node(env[i], &(*n_env));
		i++;
	}
}

char	**list_to_env(t_env **start)
{
	t_env	*help;
	char	**new_env;
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	help = *start;
	while (help)
	{
		help = help->next;
		j++;
	}
	help = *start;
	new_env = malloc(sizeof(char *) * j + 1); //todo malloc check
	if (!new_env)
	{
		ft_putstr_fd("new_env malloc doesn't allocated\n", 2);
		exit(1);
	}
	i = 0;
	while (i < j)
	{
		tmp = ft_strjoin(help->name, "=");
		new_env[i] = ft_strjoin(tmp, help->data);
		i++;
		free(tmp);
		help = help->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	lvl_up(t_env **start)
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
			break ;
		}
		tmp = tmp->next;
	}
}

int	lvl_down(t_env **start)
{
	t_env	*tmp;
	int		lvl;

	tmp = *start;
	lvl = ft_atoi(tmp->data);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			lvl--;
			free(tmp->data);
			tmp->data = ft_itoa(lvl);
			break ;
		}
		tmp = tmp->next;
	}
	return (lvl);
}

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;
	char	**new_env;
	t_env	*n_env;

	if (argc != 1)
		return (1);
	signal_exit_status = 0;
	tcgetattr(0, &termios_save);
	atexit(reset_the_terminal);
	termios_save.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_save );
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
				if (!parser(line, &token, env, &n_env))
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
			exit(signal_exit_status);
	}
}