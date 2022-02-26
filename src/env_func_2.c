/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:03:45 by ghanh             #+#    #+#             */
/*   Updated: 2022/02/25 15:03:46 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env(char *name, char *data)
{
	t_env	*n_env;

	n_env = malloc(sizeof(t_env));
	if (!n_env)
		exit(1);
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

	j = -1;
	start = 0;
	name = NULL;
	while (str[++j])
	{
		if (start == 0 && str[j] == '=')
		{
			name = ft_substr(str, 0, j);
			start = j + 1;
		}
	}
	if (name == NULL)
	{
		name = ft_substr(str, 0, j);
		start = j + 1;
	}
	data = ft_substr(str, start, j);
	if (!data || !name)
		exit(1);
	add_env(&(*n_env), new_env(name, data));
}
