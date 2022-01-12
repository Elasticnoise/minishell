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

t_list *ft_lstnew(char	*str)
{
	t_list *list;

	list = malloc(sizeof(t_list *));
	if (!list)
		return (NULL);
	list->cmd = str;
	list->argv = NULL;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

int parser(char *line, t_list **head)
{
	int i;
	int prev;
	t_list *cur_l;

	i = 0;
	while (line[i] == ' ')
		i++;
	prev = i;
	while(ft_isalpha(line[i]))
		i++;
	cur_l = ft_lstnew(ft_substr(line, prev, i));
	if (cur_l == NULL)
		return (0);
	ft_lstadd_back(head, cur_l);
	while (line[i] == ' ')
		i++;
	cur_l->argv = ft_split(line + i, ' ');
	if (cur_l->argv == NULL)
		return (0);

//	//todo delete testing
//	int k = 0;
//	while (cur_l->argv[k])
//	{
//		printf("%s\t", cur_l->argv[k]);
//		k++;
//	}
//	printf("(%s)\n", cur_l->cmd);
//	printf("i = %d\n", i);

	return(1);
}


int	main(int argc, char **argv, char **env)
{
	char 	*line;
//	t_main	main;
	t_list	*list;

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
		parser(line, &list);
//		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало ctnrl + d
//		ft_get_next_line(1, &line); //чтение
//		parser(line, &main); //парсинг
		free(line);
//		status = executor(&main, env);
	}
	return (0);
}
