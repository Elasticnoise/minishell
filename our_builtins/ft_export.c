//
// Created by Gaynell Hanh on 2/17/22.
//

#include "../minishell.h"

void	set_var(t_env **env, char *key)
{
	set_one_node(key, &(*env));
}


void	print_export(t_env **env)
{
	t_env *tmp;

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

void	ft_export(t_token *token, t_env **env)
{
	int		i;
	char	*key;

	key = NULL;
//	signal_exit_status = 0;
	i = 1;
	if (!(token->cmd[i]))
		print_export(env);
	while (token->cmd[i])
	{
		key = token->cmd[i];
		if (check_var(key, token))
			set_var(env, key);
		i++;
	}
}