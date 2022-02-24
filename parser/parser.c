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

int	check_delimiter(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '|')
		return (2);
	else if (c == '<')
		return (3);
	else if (c == '>')
		return (4);
	else
		return (0);
}

int	malloc_sp(char *line)
{
	int	i;
	int	counter;
	int	len;

	counter = 0;
	i = 0;
	len = 0;
	while (line[i])
	{
		if (quotes(line, i))
			len++;
		else if (!check_delimiter(line[i]) || !counter)
		{
			len++;
			if (check_delimiter(line[i]) > 2 && line[i + 1] == line[i])
				len++;
			if (check_delimiter(line[i]))
				counter++;
			else
				counter = 0;
		}
		i++;
	}
	return (len);
}

char	set_del(int max)
{
	if (max == 1)
		return (' ');
	else if (max == 2)
		return ('|');
	else if (max == 3)
		return ('<');
	else if (max == 4)
		return ('>');
	return (0);
}

char	*destroy_space(char *line)
{
	char	*new_line;
	int		i;
	int		help;
	int		j;
	int		redir_type;

	j = 0;
	i = 0;
	new_line = malloc(sizeof(char *) * malloc_sp(line));
	while (line[i])
	{
		if (quotes(line, i) || !check_delimiter(line[i]))
			new_line[j++] = line[i];
		else
		{
			redir_type = 0;
			while (line[i] && check_delimiter(line[i]))
			{
				if (check_delimiter(line[i]) > redir_type)
				{
					redir_type = check_delimiter(line[i]);
					help = i;
				}
				i++;
			}
			new_line[j++] = set_del(redir_type);
			if (check_delimiter(line[help]) > 2 && line[help + 1]
				&& line[help] == line[help + 1])
				new_line[j++] = set_del(redir_type);
			i--;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
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
	t_token	*help;

	i = 0;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\0' && !(!new_quotes(line, i) && line[i] == '|'))
			i++;
		if (line[i] && (line[i] == '"' || line[i] == '\''))
			i++;
		add_token_back(&(*head),
			new_token(ft_substr(line, j, i - j),
				&(*env)));
		if (line[i] == '\0')
			break ;
		i++;
	}
	j = i;
	while (help)
	{
		help->cmd_i = j;
		help = help->next;
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
