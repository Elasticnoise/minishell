#include "../../minishell.h"

//static void set_dollar_help(int calloc_v, char **str, int start, t_env *help)
//{
//	char	*res;
//	int		i;
//	int		j;
//
//	res = ft_calloc(calloc_v);
//	i = 0;
//	if (!res)
//		exit(1);
//
//}

void	set_dollar(char **str, int start, t_env **env)
{
	int		i;
	char	*s;
	char	*new;
	t_env	*help;
	char	*res;
	int		end;
	int		j;

	j = 0;
	i = start;
	help = *env;
	s = *str;
	if (s[i + 1] && s[i + 1] == '?')
	{
		new = ft_itoa(signal_exit_status);
		i += 2;
		res = ft_calloc(ft_strlen(s),
						1);
		end = i;
		i = 0;
		while (i < start)
		{
			res[i] = s[i];
			i++;
		}
		while (j < ft_strlen(new))
			res[i++] = new[j++];
		while (s[end])
			res[i++] = s[end++];
		free(new);
		free(*str);
		*str = res;
		return ;
	}
	else
	{
		while (s[i] && ft_isalnum(s[i]) && !check_delimiter(s[i]) &&
			   s[i] != '\''
			   && s[i] != '"')
			i++;
		new = ft_substr(s, start + 1, i - start - 1);
		while (help)
		{
			if (!ft_strncmp(help->name, new, ft_strlen(new)))
			{
				free(new);
				break ;
			}
			help = help->next;
		}
	}
	end = i;
//	if (!new)
//		exit(1);

	if (help)
	{
		res = ft_calloc(ft_strlen(s) - (i - start) + ft_strlen(help->data) + 1,
						1);
//		if (res)
//			exit(1);
		i = 0;
		while (i < start)
		{
			res[i] = s[i];
			i++;
		}
		while (j < ft_strlen(help->data))
			res[i++] = help->data[j++];
		while (s[end])
			res[i++] = s[end++];
	}
	else
	{
		free(new);
		res = ft_calloc(ft_strlen(s) - (i - start) + 1, 1);
//		if (!res)
//			exit(1);
		i = 0;
		while (i < start)
		{
			res[i] = s[i];
			i++;
		}
		while (s[end])
			res[i++] = s[end++];
	}
	free(*str);
	*str = res;
}

