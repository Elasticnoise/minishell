/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:59:00 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 15:59:02 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*row_path;

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		row_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(row_path, cmd);
		if (row_path)
			free(row_path);
		if (access(path, F_OK) == 0)
			return (path);
		if (path)
			free(path);
		i++;
	}
	return (NULL);
}
