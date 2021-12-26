/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:09:23 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	clean_line(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	if (*line == NULL)
		return (-1);
	free(tmp);
	return (0);
}

int	check_reminder(char **remainder, char **line)
{
	char	*tmp;
	char	*p_n;

	if (*remainder)
	{
		p_n = ft_strchr(*remainder, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(*remainder);
			tmp = *remainder;
			p_n++;
			*remainder = ft_strdup(p_n);
			free(tmp);
			return (1);
		}
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	else
		*line = ft_strdup("");
	return (0);
}

int	is_line(char **reminder, char **line, char *p_n, char *buf)
{
	char	*tmp;

	*p_n = '\0';
	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	tmp = *reminder;
	p_n++;
	*reminder = ft_strdup(p_n);
	free(tmp);
	free(buf);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	size_t		bytes_read;
	char		*p_n;
	static char	*remainder;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	if (check_reminder(&remainder, line))
		return (1);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read)
	{
		buf[bytes_read] = '\0';
		p_n = ft_strchr(buf, '\n');
		if (p_n)
			return (is_line(&remainder, line, p_n, buf));
		if (clean_line(line, buf) == -1)
			return (-1);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (0);
}
