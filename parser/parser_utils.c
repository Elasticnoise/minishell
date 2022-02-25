/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:05:23 by ghanh             #+#    #+#             */
/*   Updated: 2022/02/24 21:05:24 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	spaces(int *i, int *j, char *line, char **new_line)
{
	int	redir_type;
	int	help;

	redir_type = 0;
	while (line[(*i)] && check_delimiter(line[(*i)]))
	{
		if (check_delimiter(line[(*i)]) > redir_type)
		{
			redir_type = check_delimiter(line[(*i)]);
			help = (*i);
		}
		(*i)++;
	}
	(*new_line)[(*j)++] = set_del(redir_type);
	if (check_delimiter(line[help]) > 2 && line[help + 1]
		&& line[help] == line[help + 1])
		(*new_line)[(*j)++] = set_del(redir_type);
	(*i)--;
}

char	*destroy_space(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_line = malloc(sizeof(char *) * malloc_sp(line));
	if (!new_line)
		exit(1);
	while (line[i])
	{
		if (quotes(line, i) || !check_delimiter(line[i]))
			new_line[j++] = line[i];
		else
			spaces(&i, &j, line, &new_line);
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
