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

#include "minishel.h"

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_main	main;

	while(status)
	{
		ft_putstr_fd("sh> ", 1);
		ft_get_next_line(1, &line); //чтение
		parser(line, &main); //парсинг
		free(line);
		executor(&main, env);
	}
	return (0);
}
