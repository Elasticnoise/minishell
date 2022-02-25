/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:48:30 by ghanh             #+#    #+#             */
/*   Updated: 2022/02/25 14:48:31 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	set_env(char **env, t_env **n_env)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
			flag = 1;
		if (ft_strncmp("OLDPWD=", env[i], 7))
			set_one_node(env[i], &(*n_env));
		i++;
	}
	if (!flag)
		set_one_node("SHLVL=0", &(*n_env));
	set_one_node("OLDPWD=", &(*n_env));
}

static void	list_help(int j, char ***new_env, t_env *help)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < j)
	{
		tmp = ft_strjoin(help->name, "=");
		(*new_env)[i] = ft_strjoin(tmp, help->data);
		if (!tmp || !(*new_env))
			exit(1);
		i++;
		free(tmp);
		help = help->next;
	}
	(*new_env)[i] = NULL;
}

char	**list_to_env(t_env **start)
{
	t_env	*help;
	char	**new_env;
	int		j;

	j = 0;
	help = *start;
	while (help)
	{
		help = help->next;
		j++;
	}
	help = *start;
	new_env = malloc(sizeof(char *) * j + 1);
	if (!new_env)
		exit(1);
	list_help(j, &new_env, help);
	return (new_env);
}

void	lvl_up(t_env **start, char **argv, int argc)
{
	t_env	*tmp;
	int		lvl;

	(void) argv;
	(void) argc;
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
//	if (!tmp)
//		add_env(&*(start), new_env(ft_strdup("SHLVL"), ft_strdup("1")));
//		set_one_node("SHLVL=1", start);
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
			if (!tmp->data)
				exit(1);
			break ;
		}
		tmp = tmp->next;
	}
	return (lvl);
}
