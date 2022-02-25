/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:22:32 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/25 12:22:35 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_token **cmd)
{
	int		limiter;
	int		fd;
	char	*line;

	if ((*cmd)->limiter)
	{
		fd = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			line = readline("> ");
			if (line == NULL)
				break ;
			limiter = ft_strcmp(line, (*cmd)->limiter);
			if (limiter == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		free(line);
		(*cmd)->fd.in_file = fd;
		close(fd);
	}
}
