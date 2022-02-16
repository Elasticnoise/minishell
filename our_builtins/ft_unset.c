#include "../minishell.h"

//void	del_var(t_env **env, char *key)
//{
//	t_env	*lst;
//	t_env	*prev;
//	t_env	*var;
//
//	lst = *env;
//	var = lst;
//	if (!ft_strcmp(var->name, key))
//	{
//		*env = lst->next;
//		ft_lstdelone(lst, del_content);
//		return ;
//	}
//	while (lst->next)
//	{
//		prev = lst;
//		lst = lst->next;
//		var = lst;
//		if (!ft_strcmp(var->name, key))
//		{
//			prev->next = lst->next;
//			ft_lstdelone(lst, del_content);
//			return ;
//		}
//	}
//}

//void	ft_unset(t_token *token, t_env *env)
//{
//	int		i;
//	char	*key;
//
//	key = NULL;
//	signal_exit_status = 0;
//	i = 1;
//	while (token->cmd[i])
//	{
//		key = get_key(token->cmd[i]);
//		if (check_key(key))
//			del_var(&env, key);
//		else
//		{
//			signal_exit_status = 1;
//			ft_putstr_fd("minishell: unset: \'", 2);
//			ft_putstr_fd(key, 2);
//			ft_putstr_fd("\': not a valid identifier\n", 2);
//		}
//		free(key);
//		i++;
//	}
//}

