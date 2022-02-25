/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:33:11 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 21:33:13 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	new_str(char **str, int len)
{
	int		i;
	char	*new;
	int		j;
	char	help;

	i = 0;
	j = 0;
	new = ft_calloc(len + 1, 1);
	if (!new)
		exit(1);
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			help = (*str)[i++];
			while ((*str)[i] != help)
				new[j++] = (*str)[i++];
			i++;
		}
		else
			new[j++] = (*str)[i++];
	}
	new[j] = '\0';
	free(*str);
	*str = new;
}

static void	double_qoutes(char **string, t_env **env, int *len, int *i)
{
	int	help;

	(*len) -= 2;
	help = (*i);
	while ((*string)[++(*i)] != '"')
	{
		if ((*string)[(*i)] == '$' && (((*string)[(*i) - 1]
		&& (*string)[(*i) - 1] == '$') || ((*string)[(*i) + 1] && (*string)[(*i)
		+ 1] == '$')))
			continue ;
		if ((*string)[(*i)] == '$')
		{
			set_dollar(&(*string), *i, env);
			(*i) = help;
			(*len)--;
		}
	}
}

static void	one_qoutes(char **string, int *len, int *i)
{
	(*len) -= 2;
	(*i)++;
	while ((*string)[(*i)] != '\'')
		(*i)++;
}

void	delete_quotes(char **string, t_env **env)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while ((*string)[i])
	{
		if ((*string)[i] == '"')
			double_qoutes(&(*string), env, &len, &i);
		else if ((*string)[i] == '\'')
			one_qoutes(&(*string), &len, &i);
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
