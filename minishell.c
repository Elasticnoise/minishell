/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:41:55 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/25 19:41:57 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	parser(char *line, t_main *main)
//{
//	return ;
//}
//
//void	init_param(t_main *main, char **argv, char **envp)
//{
//	char **cmd;
//
//	cmd = ft_split(argv[1], ' ');
//}

//t_list *ft_lstnew(char	*str)
//{
//	t_list *list;
//
//	list = malloc(sizeof(t_list *));
//	if (!list)
//		return (NULL);
//	list->cmd = str;
//	list->argv = NULL;
//	list->next = NULL;
//	return (list);
//}
//



char	*set_var(char *line, int i, char **env)
{
	char	*begin;
	char	*end;
	char	*var;
	char	*var_value;
	int		j;

	i++;
	j = i;
	begin = ft_substr(line, 0, i);
	while (line[j] != ' ')
		j++;
	if (j != i)
		var_value = "$";
	else
		var_value = ft_substr(env[i], ft_strlen(var) + 1,
							  ft_strlen(env[i]) - (ft_strlen(var) + 1));
	var = ft_substr(line, i, j - i);
	end = ft_substr(line, j, ft_strlen(line) - j);
	i = 0;
	while (ft_strncmp(env[i], var, ft_strlen(var)) != 0)
		i++;
	begin = ft_strjoin(begin, var_value);
	begin = ft_strjoin(begin, " ");
	begin = ft_strjoin(begin, end);
	free(end);
	printf("'%s' -- cmd\n", var_value);
	free(var_value);
	return (begin);
}

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
//	printf("Check Succeed\n"); //todo delete print
	return (0);
}

//void	ft_lstadd_back(t_list **lst, t_list *new)
//{
//	t_list	*tmp;
//
//	tmp = *lst;
//	if (tmp)
//	{
//		while (tmp->next)
//			tmp = tmp->next;
//		tmp->next = new;
//	}
//	else
//		*lst = new;
//}

t_token *new_token(char	*str)
{
	t_token *token;

	token = malloc(sizeof(t_token *));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = CHAR_NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void add_token_back(t_token **head, t_token *new)
{
	t_token *tmp;
	t_token *prev_help;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
		{
			prev_help = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		tmp->prev = prev_help;
	}
	else
		*head = new;
}


//void	free_list(t_list *a)
//{
//	t_list	*help;
//
//	while (a)
//	{
//		help = a->next;
//		free(a);
//		a = help;
//	}
//}
t_token *get_tokens(char *line)
{
	t_token *head;
	int		i;
	int 	j;

	i = 0;
	head = NULL;
	while (line[i])
	{
		j = i;
		while (line[i] != '\0' && (line[i] != '<' && line[i] != '>'
								   && line[i] != '|'))
			i++;
		add_token_back(&head, new_token(ft_substr(line, j, i)));
		i++;
	}
	//	while (head)
	//	{
	printf("|%s| -string\n", head->str);
	//		head = head->next;
	//	}
	////free list;
	t_token *help;
	while (head)
	{
		help = head->next;
		free(head);
		head = help;
	}

}

char *destroy_space(char *line)
{
	char	*new_line;
	int		i;
	int		counter;
	int 	j;

	j = 0;
	i = 0;
	counter = 1;
	new_line = malloc(sizeof(char *) * ft_strlen(line) + 1);
	//todo malloc check or malloc for correct size
	while (line[i])
	{
		if (quotes(line, i))
			new_line[j++] = line[i];
		else if (!counter || (line[i] != ' '))
		{
			new_line[j++] = line[i];
			if (line[i] == ' ')
				counter++;
			else
				counter = 0;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
//int	skip(char *line, char quote, int i)
//{
//	while(line[++i] != quote)
//	{}
//	return (i);
//}

int parser(char *line, t_main *main, char *env[])
{
	int i;
	int prev;

//	line = set_var(line, 5, env); //echo
//	printf("%s\n", line);
//	i = 0;
	if (quotes(line, 0)) //todo quotes check
		return (printf("Quotes didnt close\n"));
	line = destroy_space(line);
	printf("New line: |%s|\n", line);
	main->head = get_tokens(line);
//	free(line);
//	printf("Line: !%s!\n", line);

	//todo add check ; and | and '\'

//	while (line[i] != '\0')
//	{
//		if (line[i] == '"' || line[i] == '\'')
//			i = skip(line, line[i], i);
//		i++;
//	}
// 	i = 0;
//	while (line[i] == ' ')
//		i++;
//	prev = i;
//	prev = 0;
//	while(ft_isalpha(line[i]))
//		i++;
//	cur_l = ft_lstnew(ft_substr(line, prev, i));
//	if (cur_l == NULL)
//		return (0);
//	ft_lstadd_back(head, cur_l);
//	while (line[i] == ' ')
//		i++;
//	cur_l->argv = ft_split(line + i, ' ');
//	if (cur_l->argv == NULL)
//		return (0);
//
////	//todo delete testing
//	int k = 0;
//	printf("(%s)\n", cur_l->cmd);
//	while (cur_l->argv[k])
//	{
//		printf("%s\n", cur_l->argv[k]);
//		k++;
//	}
//	printf("k = %d\n", k);

	return(0);
}


int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_main	main;

	(void)	argv;
	(void)	argc;
	(void)	(env);
	if (argc != 1)
		return (1);

	while(1)
	{
//		ft_putstr_fd("sh> ", 1);
//		get_next_line(1 , &line);
		line = readline(BEGIN(49, 34)"Shkad $ "CLOSE);
		if (line && *line)
			add_history(line);
		parser(line, &main, env);
//		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало ctnrl + d
//		free(line);
//		free_list(list);
//		status = executor(&main, env);
	}
	return (0);
}
