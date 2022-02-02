//
// Created by Gaynell Hanh on 2/2/22.
//

#include "../minishell.h"

int quotes(char *line, int i)
{
	char *help;
	char *str;

	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
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

int check_delimiter(char c)
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

int		malloc_sp(char *line)
{
	int i;
	int counter;
	int len;

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
	int		counter;
	int 	j;
	int 	max;

	j = 0;
	max = 0;
	i = 0;
	counter = 1;
	new_line = malloc(sizeof(char *) * malloc_sp(line));
	while (line[i])
	{
		if (quotes(line, i))
			new_line[j++] = line[i];
		else if (!check_delimiter(line[i]))
			new_line[j++] = line[i];
		else
		{
			max = 0;
			while (line[i] && check_delimiter(line[i]))
			{
				if (check_delimiter(line[i]) > max)
					max = check_delimiter(line[i]);
				i++;
			}
			new_line[j++] = set_del(max);
			if (check_delimiter(line[i - 1]) > 2 && line[i - 2] && line[i - 1]
			== line[i - 2])
				new_line[j++] = set_del(max);
			i--;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}


t_token *new_token(char	*str)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = str;
	token->type = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token *tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*head = new;
}

void get_tokens(char *line, t_token **head)
{
	t_token *help;
	int		i;
	int 	j;

	i = 0;
//	help = *head;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\0' && (!quotes(line, i) && line[i] != '<' &&
								   line[i] != '>' && line[i] != '|'))
			i++;
		if (line[i] && (line[i] == '"' ||  line[i] == '\''))
			i++;
		add_token_back(&(*head), new_token(ft_substr(line, j, i - j)));
//		printf("%d -- i %d --- j\n", i , j);
//		add_token_back(&(*head), new_token("hello"));
//	(*head)->next = new_token("Raz");
//	printf("%p\n",(*head)->next->next);
//	(*head)->next->next = new_token("Tri"); //////// BUS ERROR
//		add_token_back(&(*head), new_token(ft_substr(line, j, i - j)));
//	add_token_back(&head, new_token(ft_substr(line, j, i - j)));
//		printf("%d -- i j\n", i - j);
		if (line[i] == '\0')
			break ;
		i++;
	}

	help = *head;
	while (help)
	{
		printf("{%s} -- token\n", help->cmd);
		help = help->next;
	}

	help = *head;
//	while (*head)
//	{
//		help = (*help).next;
//		free((*help).cmd);
//		help = *head;
//	}
//	return (*help);
}

int delim_check(char *line)
{
	int i;

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
				if (line[i] && check_delimiter(line[i]) > 2 && line[i] ==
				line[i - 1])
					i++;
				if (!line[i] || check_delimiter(line[i]) > 1)
					return (1);
			}
			i++;
		}
	}
	return (0);
}

int parser(char *line, t_token **token, char *env[])
{
	int i;
	int prev;
	t_token *head;

	head = *token;
	if (quotes(line, 0)) //todo quotes check
		return (printf("Quotes didnt close\n"));
	if (delim_check(line))
		return (printf("Pipes/redirect didn't close\n"));
	line = destroy_space(line);
	printf("New line: |%s|\n", line);
//	printf ("%d and %d and %d and %d\n", ' ', '|', '>', '<');
//	//	head = NULL;
	get_tokens(line, &head);
//	*token = head;
	return(0);
}