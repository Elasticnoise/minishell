#include "../minishell.h"

void	ft_lstdelone(t_env *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->data);
	free(lst);
}

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

void	del_node(void *content)
{
	t_env	*token;

	token = content;
	free(token->data);
	free(token->name);
	free(content);
}

void	del_var(t_env **env, char *key)
{
	t_env	*lst;
	t_env	*prev;
	t_env	*var;

	lst = *env;
	var = lst;
	if (!ft_strcmp(var->name, key))
	{
//		printf("!!!!!\n");
		*env = lst->next;
		ft_lstdelone(lst, del_node);
		return ;
	}
	while (lst->next)
	{
		prev = lst;
		lst = lst->next;
		var = lst;
		if (!ft_strcmp(var->name, key))
		{
			printf("!!!!!\n");
			prev->next = lst->next;
			ft_lstdelone(lst, del_node);
			return ;
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

