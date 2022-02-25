/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:01:02 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/26 19:01:05 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_right_env(char **envp, char *right_envp)
{
	int		i;
	char	*result;

	i = 0;
	while (ft_strnstr(envp[i], right_envp,
			ft_strlen(envp[i])) == 0)
		i++;
	result = envp[i] + ft_strlen(right_envp) + 1;
	if (result != NULL)
		return (result);
	return (NULL);
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

int	ft_set_var(t_token *token, t_env **n_env, char *key, char *value)
{
	t_token	*list;
	t_env	*env;

	list = token;
	env = *n_env;
	while (list)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			if (env->data)
				free(env->data);
			env->data = value;
			return (1);
		}
		list = list->next;
	}
	return (0);
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
