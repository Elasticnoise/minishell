/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 15:37:20 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/26 15:37:23 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int 	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
//	if (ft_strncmp(cmd, "cd", 3) == 0)
//		return (2);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
//		exit(126);
	return (0);
}

void	do_builtins(t_token *token, char **env, t_env **n_env)
{
//	if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
//		signal_exit_status = ft_cd(token, env);
	if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
		ft_pwd(token);
	else if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
		ft_echo(token);
	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
		ft_env(token, n_env);
	else if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
		ft_exit(token, n_env);
	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
		ft_unset(token, *n_env);
	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
		ft_export(token, n_env);
}

int 	ft_pwd(t_token *token)
{
	char	*tmp_buf;
	char	*pwd;

	(void)token;
	tmp_buf = NULL;
	pwd = getcwd(tmp_buf, 0);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(tmp_buf);
	free(pwd);
	return (0);
}

void	free_doublechar(char **new_env)
{
	int	i;

	i = 0;
	if (new_env)
	{
		while (new_env[i])
			free(new_env[i++]);
		free(new_env);
	}
}

void	ft_env(t_token *token, t_env **n_env)
{
	t_env *tmp;

	tmp = *n_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->data, ""))
		{
			printf("%s", tmp->name);
			printf("=%s\n", tmp->data);
		}
		tmp = tmp->next;
	}
}

int 	ft_cd(char **env)
{
	return (0);
}

int	get_shlvl(t_env **n_env)
{
	t_env	*tmp;
	int		lvl;

	tmp = *n_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			break;
		}
		tmp = tmp->next;
	}
	return (lvl);
}
