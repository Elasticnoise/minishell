#include "../minishell.h"

int	check_var(char *key, t_token *token)
{
	if (ft_isalpha(key[0]) || key[0] == '_')
		return (1);
	signal_exit_status = EXIT_FAILURE;
	ft_putstr_fd("Shkad: ", 2);
	ft_putstr_fd(token->cmd[0], 2);
	ft_putstr_fd(": \'", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (0);
}

void free_env_node(t_env *env)
{
	free(env->name);
	if (env->data)
		free(env->data);
	free(env);
}

void	del_var(t_env **env, char *key)
{
	t_env *tmp;
	t_env *prev;

	tmp = (*env)->next;
	prev = *env;
	if (!ft_strcmp(prev->name, key))
	{
		free_env_node(prev);
		*env = tmp;
	}
	else
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, key))
			{
				*env = prev;
				prev->next = tmp->next;
				free_env_node(tmp);
				break ;
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
}

void	ft_unset(t_token *token, t_env *env)
{
	int		i;
	char	*key;

	key = NULL;
	signal_exit_status = 0;
	i = 1;
	while (token->cmd[i])
	{
		key = token->cmd[i];
		if (check_var(key, token))
			del_var(&env, key);
		i++;
	}
}
