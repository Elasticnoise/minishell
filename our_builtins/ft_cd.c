/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:36:57 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 15:37:04 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_key(t_env **n_env, char *key)
{
	t_env	*result;

	result = *n_env;
	while (result)
	{
		if (!ft_strcmp(result->name, key))
			return (result);
		result = result->next;
	}
	return (NULL);
}

static void	help(t_env **n_env, char *pwd, char *old_pwd)
{
	char	*help;

	del_var(n_env, "PWD");
	del_var(n_env, "OLDPWD");
	help = ft_strjoin("PWD=", pwd);
	set_var(n_env, help);
	free(help);
	help = ft_strjoin("OLDPWD=", old_pwd);
	set_var(n_env, help);
	free(help);
}

int	change_dir(char *path, t_token *token, t_env **n_env)
{
	char	*old_pwd;
	char	*buf;
	char	*pwd;

	buf = NULL;
	old_pwd = getcwd(buf, 0);
	free(buf);
	if (chdir(path) == 0)
	{
		buf = NULL;
		pwd = getcwd(buf, 0);
		free(buf);
		help(n_env, pwd, old_pwd);
		free (pwd);
		free (old_pwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("Shkad: cd: ", 2);
		ft_putstr_fd(token->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
}

int	ft_cd(t_token *token, t_env **n_env)
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
