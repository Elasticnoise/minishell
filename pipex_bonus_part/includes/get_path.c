#include "../pipex.h"
#include  <stdio.h>

char *get_path(char **envp, char *cmd)
{
	int i;
	char **paths;
	char *path;
	char *row_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i]) == 0))
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