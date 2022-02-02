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
//	free(var_value);
	return (begin);
}

//int pipes(char *line)
//{
//	int i;
//	int len;
//
//	len = ft_strlen(line);
//	i = 0;
//	while (line[i])
//	{
//		i++;
//	}
//}


//int executor(t_token *node)
//{
//	t_token *cmd;
//
//	cmd = node;
//	while (cmd != NULL)
//	{
//		if (INT_HEREDOC)
//		{
//			return (0);
//		}
//		else if (INT_PIPE)
//		{
//			return (0);
//		}
//		else if ()
//
//		cmd = cmd->next;
//	}
//}

//void	set_in_out_files(t_token *token)
//{
//	if (!token->infile)
//		token->infile = 0;
//	else
//		token->infile = open(av[1], O_RDONLY); // сделать передачу команды со структуры
//	if (!token->outfile)
//		token->outfile = 1;
//	else
//		token->outfile = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
//			S_IWUSR | S_IRGRP | S_IROTH);
//	if (token->infile < 0)
//	{
//		ft_putstr_fd("cat: ", 2);
//		ft_putstr_fd(av[1], 2); // сделать передачу команды со структуры
//		ft_putstr_fd(": No such file or directory\n", 2);
//		exit (1);
//	}
//}

//int	executor(t_token **token, char **env)
//{
//	int 	in_file;
//	int 	out_file;
//	int 	i;
//	t_token	*cmd;
//
//	i = 3;
//	cmd = *token;
//
//	if (cmd)
//	{
//		set_in_out_files(*token);
//		dup2(in_file, INFILE);
//		dup2(out_file, OUTFILE);
//		ft_redirect(av, env, in_file, out_file,2);
//		while (i < ac - 2)
//			ft_redirect(av, env, in_file, out_file, i++);
//		do_exec(av, env, i);
//	}
//	return (0);
//}


int	main(int argc, char **argv, char **env)
{
	char 	*line;
//	t_main	main;
	t_token *token;
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
		parser(line, &token, env);
//		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало cntrl + d
//		free(line);
//		free_list(list);
//		status = executor(&main, env);
	}
	return (0);
}