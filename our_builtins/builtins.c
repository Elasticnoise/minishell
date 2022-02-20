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

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
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
	return (0);
}

int	do_builtins(t_token *token, t_env **n_env)
{
	if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
		return (ft_cd(token, *n_env));
	if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
		return (ft_pwd(token));
	else if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
		return (ft_echo(token));
	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
		return (ft_env(n_env));
	else if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
		return (ft_exit(token, n_env));
	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
		return (ft_unset(token, n_env));
	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
		return (ft_export(token, n_env));
	else
		return (EXIT_FAILURE);
}

int	ft_pwd(t_token *token)
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
	return (EXIT_SUCCESS);
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

int	ft_env(t_env **n_env)
{
	t_env	*tmp;
	int		is_path;

	is_path = 0;
	tmp = *n_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			is_path = 1;
		tmp = tmp->next;
	}
	if (is_path)
	{
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
	return (EXIT_SUCCESS);
}

t_env	*find_key(t_env *n_env, char *key)
{
	t_env	*result;

	result = n_env;
	while (result)
	{
		if (!ft_strcmp(result->name, key))
			return (result);
		result = result->next;
	}
	return (NULL);
}

int	ft_set_var(t_token *token, t_env *n_env, char *key, char *value)
{
	t_token	*list;
	t_env	*env;

	list = token;
	env = n_env;
	while (list)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			free(env->data);
			env->data = value;
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	change_dir(char *path, t_token *token, t_env *n_env)
{
	char	*old_pwd;
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = NULL;
	old_pwd = NULL;
	old_pwd = getcwd(buf, 0);
	free(buf);
	if (chdir(path) == 0)
	{
		buf = NULL;
		pwd = getcwd(buf, 0);
		free(buf);
		ft_set_var(token, n_env, "PWD", pwd);
		ft_set_var(token, n_env, "OLDPWD", old_pwd);
		if (pwd)
			free (pwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(token->cmd[1], 2);
		ft_putstr_fd(": ", 2);
		write(1, "\n", 2);
		return (EXIT_FAILURE);
	}
}

int	ft_cd(t_token *token, t_env *n_env)
{
	char	*path;
	t_env	*home;

	if (token->cmd[1] == NULL)
	{
		home = find_key(n_env, "HOME");
		if (home == NULL)
		{
			ft_putstr_fd("SHKAD: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		path = (find_key(n_env, "HOME")->data);
	}
	else if (ft_strcmp(token->cmd[1], "") == 0)
		return (EXIT_SUCCESS);
	else
		path = token->cmd[1];
	return (change_dir(path, token, n_env));
}

int	get_shlvl(t_env **n_env)
{
	t_env	*tmp;
	int		lvl;

	tmp = *n_env;
	lvl = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			break ;
		}
		tmp = tmp->next;
	}
	return (lvl);
}
