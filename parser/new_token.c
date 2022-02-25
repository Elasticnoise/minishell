/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:06:05 by ghanh             #+#    #+#             */
/*   Updated: 2022/02/24 19:06:06 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	in_case(int *i, char *str, t_token **token, t_env **env)
{
	int	help;

	(*i)++;
	if (str[(*i)] == '<')
		(*i)++;
	help = (*i);
	while (str[(*i)] && !check_delimiter(str[(*i)]))
		(*i)++;
	if ((*token)->infile)
	{
		free((*token)->infile);
		close((*token)->fd.in_file);
	}
	if (str[help - 2] == '<')
	{
		if ((*token)->limiter)
			free((*token)->limiter);
		(*token)->limiter = ft_substr(str, help, (*i) - help);
	}
	else
	{
		(*token)->infile = ft_substr(str, help, (*i) - help);
		delete_quotes(&((*token)->infile), env);
		(*token)->fd.in_file = open((*token)->infile, O_RDONLY);
	}
}

static void	redir_case(int *i, char *str, t_token **token, t_env **env)
{
	int	help;

	(*i)++;
	if (str[(*i)] == '>')
		(*i)++;
	help = (*i);
	while (str[(*i)] && !check_delimiter(str[(*i)]))
		(*i)++;
	if ((*token)->outfile)
	{
		free((*token)->outfile);
		close((*token)->fd.out_file);
	}
	(*token)->outfile = ft_substr(str, help, (*i) - help);
	if (!(*token)->outfile)
		exit(1);
	delete_quotes(&((*token)->outfile), env);
	if (str[help - 2] == '>')
		(*token)->fd.out_file = open((*token)->outfile, O_APPEND | O_WRONLY
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		(*token)->fd.out_file = open((*token)->outfile, O_TRUNC | O_WRONLY
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

static void	first_case(int *i, char *str, char **new_string)
{
	int		help;
	char	*to_free;

	help = (*i);
	while (str[(*i)] && ((!check_delimiter(str[(*i)])
				|| check_delimiter(str[(*i)]) == 1) || new_quotes(str, (*i))))
		(*i)++;
	if (!(*new_string))
		(*new_string) = ft_substr(str, help, (*i) - help);
	else
	{
		to_free = ft_substr(str, help, (*i) - help);
		if (!to_free)
			exit(1);
		(*new_string) = ft_strjoin(*new_string, to_free);
	}
	if (!(*new_string))
		exit(1);
}

void	end_of_token(t_token **token, t_env **env, char	*new_string, char *str)
{
	int	i;

	if ((*token)->fd.in_file != -1 && (*token)->fd.out_file != -1)
	{
		(*token)->cmd = ft_q_split(new_string, ' ');
		if (!(*token)->cmd)
			exit(1);
	}
	free(new_string);
	free(str);
	i = 0;
	if ((*token)->cmd)
	{
		while ((*token)->cmd[i])
		{
			delete_quotes(&((*token)->cmd[i]), env);
			i++;
		}
	}
}

t_token	*new_token(char	*str, t_env **env)
{
	t_token	*token;
	int		i;
	char	*new_string;

	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	ft_memset((void *)token, 0, sizeof(t_token));
	token->next = NULL;
	new_string = NULL;
	while (str[i])
	{
		if (!check_delimiter(str[i]) || check_delimiter(str[i]) == 1
			|| quotes(str, i))
			first_case(&i, str, &new_string);
		else if (check_delimiter(str[i]) == 4)
			redir_case(&i, str, &token, env);
		else if (check_delimiter(str[i]) == 3)
			in_case(&i, str, &token, env);
		else
			i++;
	}
	end_of_token(&token, env, new_string, str);
	return (token);
}
