//
// Created by Gaynell Hanh on 2/16/22.
//

#include "../minishell.h"

//void set_dollar2(char **str, int start, t_env **env)
//{
//	char	*s;
//	char	*new;
//	t_env	*help;
//	char	*res;
//	int		i;
//
//	s = str;
//
//}
void new_str(char **str, int len)
{
	int i;
	char *new;
	int j;
	char help;

	i = 0;
	j = 0;
	new = ft_calloc(len + 1, 1);
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			help = (*str)[i++];
			while ((*str)[i] != help)
			{
				new[j] = (*str)[i];
				j++;
				i++;
			}
			i++;
		}
		else
		{
			new[j] = (*str)[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	free(*str);
	*str = new;
}

void delete_quotes(char **string, t_env **env) //todo call this func for each str
{
	int i;
	int len;

	len = 0;
	i = 0;

	while ((*string)[i])
	{
		if ((*string)[i] == '"')
		{
			len -= 2;
			while ((*string)[++i] != '"')
				if ((*string)[i] == '$')
				{
					set_dollar(&(*string), i, env);
					len--;
				}
		}
		else if ((*string)[i] == '\'')
		{
			len -= 2;
			i++;
			while ((*string)[i] != '\'')
				i++;
		}
		else if ((*string)[i] == '$')
		{
			set_dollar(&(*string), i, env);
			len--;
		}
		i++;
	}
	len += ft_strlen(*string);
	if (len < 0)
		len = 0;
	new_str(&(*string), len);
}