/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:57:00 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 21:57:01 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

static void	question_case(int i, char *s, char **str, int j)
{
	char	*new;
	char	*res;
	int		start;
	int		end;

	start = i - 2;
	end = i;
	new = ft_itoa(g_exit_status);
	res = ft_calloc(ft_strlen(s), 1);
	if (!new || !res)
		exit(EXIT_FAILURE);
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
}

void	if_help(char **str, int i, t_env *help, int start)
{
	char	*res;
	int		end;
	int		j;

	j = 0;
	end = i;
	res = ft_calloc(ft_strlen((*str)) - (i - start)
			+ ft_strlen(help->data) + 1, 1);
	i = 0;
	while (i < start)
	{
		res[i] = (*str)[i];
		i++;
	}
	while (j < ft_strlen(help->data))
		res[i++] = help->data[j++];
	while ((*str)[end])
		res[i++] = (*str)[end++];
	free(*str);
	*str = res;
}

void	if_not_help(char **str, int start, int i, char	*s)
{
	char	*res;
	int		end;

	res = ft_calloc(ft_strlen(s) - (i - start) + 1, 1);
	end = i;
	i = 0;
	while (i < start)
	{
		res[i] = s[i];
		i++;
	}
	while (s[end])
	{
		res[i] = s[end];
		i++;
		end++;
	}
	free(*str);
	*str = res;
}

void	not_question(int start, char **str, t_env **env, char *s)
{
	int		i;
	char	*new;
	t_env	*help;

	i = start + 1;
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	new = ft_substr((*str), start + 1, i - start - 1);
	if (!new)
		exit(1);
	help = find_help(env, new);
	if (help)
		return (if_help(str, i, help, start));
	else
	{
		free(new);
		return (if_not_help(str, start, i, s));
	}
}

void	set_dollar(char **str, int start, t_env **env)
{
	char	*s;
	int		j;

	j = 0;
	s = *str;
	if (!s[start + 1] || s[start + 1] == ' ' || s[start + 1] == '$')
		return ;
	if (s[start + 1] && s[start + 1] == '?')
		return (question_case(start + 2, s, str, j));
	else
		return (not_question(start, str, env, s));
}
