//
// Created by Gaynell Hanh on 2/13/22.
//

#include "../../minishell.h"

void	set_dollar(char **str, int start, t_env **env)
{

	int i = start;
	char *s;
	char *new;
	t_env *help;
	char *res;
	int end;

	help = *env;
	s = *str;
	while (s[i] && !check_delimiter(s[i]) && s[i] != '\'' && s[i] != '"')
		i++;
	end = i;
	new = ft_substr(s, start + 1, i - start - 1); //todo malloc check
	while (help)
	{
		if (!ft_strncmp(help->name, new, ft_strlen(new)))
		{
			free(new);
			break ;
		}
		help = help->next;
	}
	if (help)
	{
		res = ft_calloc(ft_strlen(s) - (i - start) + ft_strlen(help->data) + 1,
						1);
		i = 0;
		while (i < start)
		{
			res[i] = s[i];
			i++;
		}
		int j = 0;
		while (j < ft_strlen(help->data))
		{
			res[i] = help->data[j];
			i++;
			j++;
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
}

void dollar_cmd(t_token **token, t_env **env)
{
	int i;
	int j;

	i = 0;
	while ((*token)->cmd && (*token)->cmd[i])
	{
		if ((*token)->cmd[i][0] == '\'')
		{
			i++;
			continue;
		}
		j = 0;
		while ((*token)->cmd[i][j])
		{
			if ((*token)->cmd[i][j] == '$' && (*token)->cmd[i][j + 1] &&
			 !check_delimiter((*token)->cmd[i][j + 1]) &&
				(*token)->cmd[i][j + 1] != '\'' && (*token)->cmd[i][j + 1] != '"')
			{
				set_dollar(&(*token)->cmd[i], j, &(*env));
				j = 0; //todo maybe to delete
			}
			j++;
		}
		i++;
	}
}

void dollar_infile(t_token **token, t_env **env)
{
	int i;

	i = 0;
	if (*token && (*token)->infile)
	{
		while ((*token)->infile[i])
		{
			if ((*token)->infile[0] == '\'')
				return ;
			if((*token)->infile[i] == '$' && (*token)->infile[i + 1] &&
			!check_delimiter((*token)->infile[i + 1]) && (*token)->infile[i +
			1] != '\'' && (*token)->infile[i] != '"' )
			{
				set_dollar(&(*token)->infile, i, &(*env));
				i = 0;
			}
			i++;
		}
	}
}

void dollar_outfile(t_token **token, t_env **env)
{

	int i;

	i = 0;
	if (*token && (*token)->outfile)
	{
		while ((*token)->outfile[i])
		{
			if ((*token)->outfile[0] == '\'')
				return ;
			if((*token)->outfile[i] == '$' && (*token)->outfile[i + 1] &&
			   !check_delimiter((*token)->outfile[i + 1]) && (*token)->outfile[i +
																			 1] != '\'' && (*token)->outfile[i + 1] != '"' )
			{
				set_dollar(&(*token)->outfile, i, &(*env));
				i = 0;
			}
			i++;
		}
	}
}
