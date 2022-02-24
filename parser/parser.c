/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:36:02 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 21:36:07 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	quotes(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!(line[i]))
				return (1);
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (!(line[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
}

void	get_tokens(char *line, t_token **head, t_env **env)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\0' && !(!new_quotes(line, i) && line[i] == '|'))
			i++;
		if (line[i] && (line[i] == '"' || line[i] == '\''))
			i++;
		add_token_back(&(*head), new_token(ft_substr(line,
					j, i - j), &(*env)));
		if (line[i] == '\0')
			break ;
		i++;
	}
}

int	delim_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (quotes(line, i))
			i++;
		else
		{
			if (check_delimiter(line[i]) > 1)
			{
				i++;
				while (line[i] && check_delimiter(line[i]) == 1)
					i++;
				if (line[i] && check_delimiter(line[i]) > 2
					&& line[i] == line[i - 1])
					i++;
				if (!line[i] || (check_delimiter(line[i]) != 0
						&& check_delimiter(line[i]) != 1))
					return (1);
			}
			i++;
		}
	}
	return (0);
}

int	parser(char *line, t_token **token, char *env[], t_env **n_env)
{
	t_token	*head;

	(void) env;
	head = *token;
	if (quotes(line, 0))
		return (printf("Quotes didnt close\n"));
	if (delim_check(line))
		return (printf("Pipes/redirect didn't close\n"));
	line = destroy_space(line);
	if (!ft_strcmp(line, " "))
	{
		free(line);
		return (1);
	}
	get_tokens(line, &head, &(*n_env));
	free(line);
	*token = head;
	return (0);
}
