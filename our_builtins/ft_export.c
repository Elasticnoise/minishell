/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:55:43 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 15:55:53 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	set_var(t_env **env, char *key)
{
	set_one_node(key, &(*env));
}

void	print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (ft_strcmp(tmp->data, ""))
			printf("=\"%s\"\n", tmp->data);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

int	find_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_export(t_token *token, t_env **env)
{
	int		i;
	char	*key;
	char	*help;

	key = NULL;
	i = 1;
	if (!(token->cmd[i]))
		print_export(env);
	while (token->cmd[i])
	{
		key = token->cmd[i];
		if (check_var(key, token))
		{
			help = ft_substr(key, 0, find_len(key));
			if (!help)
				exit(1);
			del_var(env, help);
			free(help);
			set_var(env, key);
		}
		i++;
	}
	return (1);
}
