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

void	parser(char *line, t_main *main)
{
	return ;
}

void	init_param(t_main *main, char **argv, char **envp)
{
	char **cmd;

	cmd = ft_split(argv[1], ' ');
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
	while(status)
	{
		ft_putstr_fd("sh> ", 1);
		line = get_next_line(1 , &line);
//		ft_get_next_line(1, &line); //чтение
//		parser(line, &main); //парсинг
		free(line);
//		status = executor(&main, env);
	}
	return (0);
}
