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

t_token *new_token(void	*str)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->infile = NULL;
	token->outfile = NULL;
	token->type = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}



void	free_list(t_token *a)
{
	t_token	*help;

	while (a)
	{
		help = a->next;
		free(a);
		a = help;
	}
}

void add_token_back(t_token **head, t_token *new)
{
	t_token *tmp;
	t_token *prev_help;

	tmp = *head;

	if (tmp)
	{
//		printf("ASAS\n");
		while (tmp->next)
		{
//			prev_help = tmp;
			tmp = tmp->next;
		}
//		printf("Class\n");
//		printf("%s\n", tmp->str);
		tmp->next = new;
//		tmp->next->next = NULL;
//		tmp->prev = prev_help;
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
//	printf("!!!!!!!\n");
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\0' && (!quotes(line, i) && line[i] != '<' &&
								   line[i] != '>' && line[i] != '|'))
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
		printf("{%s} -- token\n", help->str);
		help = help->next;
	}
//	return (*help);

}


int check_delimiter(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '|' || c == '<' || c == '>')
		return (2);
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
		else if (!counter || !check_delimiter(line[i]))
		{
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

char	*destroy_space(char *line)
{
	char	*new_line;
	int		i;
	int		counter;
	int 	j;

	j = 0;
	i = 0;
	counter = 1;
	new_line = malloc(sizeof(char *) * malloc_sp(line));
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

//int 	check_pipes(char *line)
//{
//	int i;
//
//	i = 0;
//	while (line[i] != '\0')
//	{
//		if (quotes(line, i))
//			i++;
//		else
//		{
//			if (check_delimiter(line[i]) == 2)
//			{
//				if (line[i] == '>' || line[i] == '<')
//				while (line[i] != '\0')
//			}
//			i++;
//		}
//	}
//}

int parser(char *line, t_token **token, char *env[])
{
	int i;
	int prev;
	t_token *head;

	head = *token;
	if (quotes(line, 0)) //todo quotes check
		return (printf("Quotes didnt close\n"));
	line = destroy_space(line);
	printf("New line: |%s|\n", line);
//	head = NULL;
	get_tokens(line, &head);
	*token = head;
//	main->head = head;

//	t_token *help;
//	while (main->head)
//	{
//		help = main->head->next;
//		free(main->head->str);
//		free(main->head);
//		main->head = help;
//	}
//	main->head = NULL;
//	free(line);


//	exit(0);
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

void	set_in_out_files(t_token *token)
{
	if (token->infile)
		token->fd.in_file = open(token->infile, O_RDONLY);
	else
		token->fd.in_file = 0;
	if (token->outfile)
		token->fd.out_file = open(token->outfile, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
	else
		token->fd.out_file = 1;
	if (token->fd.in_file < 0)
	{
		ft_putstr_fd("cat: ", 2);
		ft_putstr_fd(token->infile, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
//	printf("in_file=%d\n", token->fd.in_file);
//	printf("out_file=%d\n", token->fd.out_file);
}

void	do_exec_dev(t_token *token, char **envp)
{
//	char	**cmd;

//	cmd = ft_split(token, ' ');

	if (execve(get_path(envp, token->str), &token->str, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd("\n", 2);
//		free(cmd);
	}
//	free(cmd);
}

int	ft_redirect_dev(t_token *token, char **env)
{
	int		pid;
	pid_t	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (1);
	}
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN);
//		waitpid(pid, NULL, 0);
//		write(1, "!!!!!!\n", 7);
	}
	else
	{
//		write(1, "!!!!!!\n", 7);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT);
		do_exec_dev(token, env);
	}
	return (0);
}

/*TODO непрвильно отрабатывает executor*/
int	executor(t_token **token, char **env)
{
	t_token	*cmd;
	t_token	*tmp;

	cmd = *token;

	if (cmd)
	{
		set_in_out_files(cmd);
		dup2(cmd->fd.in_file, INFILE);
		dup2(cmd->fd.out_file, OUTFILE);
//		printf("!!!!!!!!!!!!%s\n", cmd->str);

		ft_redirect_dev(cmd, env);
//		cmd = cmd->next;
		tmp = cmd;
		tmp = tmp->next;
		if (tmp)
		{
//			printf("?%s\n", cmd->str);
//			cmd = cmd->next;
			while (cmd->next)
			{
//				printf("??%s\n", cmd->str);
				ft_redirect_dev(cmd, env);
				tmp = cmd;
				cmd = cmd->next;
//				printf("???%s\n", cmd->str);
			}
			do_exec_dev(cmd, env);
		}
//		while (cmd)
//		{
//			ft_redirect_dev(cmd, env);
//			cmd = cmd->next;
//			printf("!!!!\n");
//		}
		else
			do_exec_dev(cmd, env);
	}
	return (EXIT_FAILURE);
}


int	main(int argc, char **argv, char **env)
{
	char 	*line;
	int 	status;
	t_main	main;
	t_token *token;
	(void)	argv;
	(void)	argc;
	(void)	(env);
	if (argc != 1)
		return (1);

	status = 1;

	while(1)
	{
//		ft_putstr_fd("sh> ", 1);
//		get_next_line(1 , &line);
		line = readline(BEGIN(49, 34)"Shkad $ "CLOSE);
		if (line && *line)
			add_history(line);
		parser(line, &token, env);
//		ft_exit(&token);
//		rl_on_new_line();
//		rl_redisplay(); //todo Ф-ция для того, чтобы работало cntrl + d
//		free(line);
//		free_list(token);
//		status = executor(&token, env);
		executor(&token, env);
	}
	return (0);
}
