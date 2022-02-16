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
	int		help;
	int 	j;
	int 	redir_type;

	j = 0;
	i = 0;
	new_line = malloc(sizeof(char *) * malloc_sp(line));
	while (line[i])
	{
		if (quotes(line, i))
			new_line[j++] = line[i];
		else if (!check_delimiter(line[i]))
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
			if (check_delimiter(line[help]) > 2 && line[help + 1] && line[help]
			== line[help + 1])
				new_line[j++] = set_del(redir_type);
			i--;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

t_token *new_token(char	*str, t_env **env)
{
	t_token *token;
	int		i;
	int		help;
	char 	*new_string;
	char	*to_free;
	char	*to_free2;
	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_memset((void *)token, 0, sizeof(t_token));
	token->str = str;
	token->next = NULL;
	token->prev = NULL;
	to_free2 = NULL;
	new_string = NULL;
	while (str[i])
	{
		if (!check_delimiter(str[i]) || check_delimiter(str[i]) == 1 ||
		quotes(str, i))
		{
			help = i;
			while (str[i] && ((!check_delimiter(str[i]) || check_delimiter
			(str[i]) == 1)))
				i++;
			to_free = new_string;
			if (!new_string)
				new_string = ft_substr(str, help, i - help);
			else
			{
				to_free2 = ft_substr(str, help, i - help);
				new_string = ft_strjoin(new_string, to_free2);
			}
//			printf("%p -- to_free2, %p - to_free", to_free2, to_free);
//			if (to_free)
//				free(to_free);
//			free(to_free2); //todo add clean
		}
		else if (check_delimiter(str[i]) == 4)
		{
			i++;
			if (str[i] == '>')
				i++;
			help = i;
			while(str[i] && !check_delimiter(str[i]))
				i++;
			if (token->outfile)
			{
				free(token->outfile);
				close(token->fd.out_file);
			}
			token->outfile = ft_substr(str, help, i - help);
			dollar_outfile(&token, env);
			if (str[help - 2] == '>')
				token->fd.out_file = open(token->outfile, O_APPEND |
														  O_WRONLY | O_CREAT,
										  S_IRUSR |
										  S_IWUSR | S_IRGRP | S_IROTH);
			else
				token->fd.out_file = open(token->outfile,
										  O_TRUNC | O_WRONLY | O_CREAT,
										  S_IRUSR |
										  S_IWUSR | S_IRGRP | S_IROTH);
		}
		else if (check_delimiter(str[i]) == 3)
		{
			i++;
			if (str[i] == '<')
				i++;
			help = i;
			while(str[i] && !check_delimiter(str[i]))
				i++;
			if (token->infile)
			{
				free(token->infile);
				close(token->fd.in_file);
			}
			if (str[help - 2] == '<')
			{
				if (token->limiter)
					free(token->limiter);
				token->limiter = ft_substr(str, help, i - help);
			}
			else
			{
				token->infile = ft_substr(str, help, i - help);
				dollar_infile(&token, env);
				token->fd.in_file = open(token->infile, O_RDONLY); //TODO ADD IF
				if (token->fd.in_file == -1)
				{
					printf("Cannot read from file\n");
				}
			}
		}
		else
			i++;
	}
//	printf("%s -- cmd str\n", new_string);
	token->cmd = ft_q_split(new_string, ' ');
	free(new_string);
//	printf("%s -- cmd str\n", new_string);

//	dollar_cmd(&token, env);
	////todo under is func to delete first """ or "'"
//	i = 0;
//	char *tmp;
//	while (token->cmd[i])
//	{
//		if (token->cmd[i][0] == '"' || token->cmd[i][0] == '\'')
//		{
//			tmp = token->cmd[i];
//			token->cmd[i] = ft_substr(token->cmd[i], 1, ft_strlen(tmp) - 1);
//			free(tmp);
//		}
//		i++;
//	}
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

void get_tokens(char *line, t_token **head, t_env **env)
{
	t_token *help;
	int		i;
	int 	j;

	i = 0;
//	help = *head;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\0' && !(!quotes(line, i) && line[i] == '|'))
			i++;
		if (line[i] && (line[i] == '"' ||  line[i] == '\''))
			i++;
		add_token_back(&(*head), new_token(ft_substr(line, j, i - j), &(*env)) );
		if (line[i] == '\0')
			break ;
		i++;
	}

	help = *head;
	while (help)
	{
		i = 0;
		while (help->cmd && help->cmd[i])
		{
			delete_quotes(&(help->cmd[i]), env); //todo dont forget to move it
			if (i == 0)
				printf("CMD:    |%s|\n", help->cmd[i]);
			else
				printf("ARG №%d: |%s|\n", i, help->cmd[i]);

			i++;
		}
		printf("%s (outfile Name) and %d (outfile fd)\n", help->outfile,
			   help->fd.out_file);
		printf("%s (infile Name) and %d (infile fd)\n", help->infile,
			   help->fd.in_file);
		help = help->next;
	}
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

int parser(char *line, t_token **token, char *env[], t_env **n_env)
{
	t_token *head;

	head = *token;
	if (quotes(line, 0)) //todo quotes check
		return (printf("Quotes didnt close\n"));
	if (delim_check(line))
		return (printf("Pipes/redirect didn't close\n"));
	line = destroy_space(line);
	get_tokens(line, &head, &(*n_env));
	free(line);
	*token = head; ////  Чтобы работало в мейне
	return(0);
}