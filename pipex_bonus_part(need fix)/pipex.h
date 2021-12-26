#ifndef PIPEX_H
# define PIPEX_H

#include <string.h>
#include <stdio.h>
#include "libft/libft.h"

char	*find_path(char **envp);

void	ft_strdel(char **as);

char	*search_path(char **paths, char *cmd);

void	free_arr(char ***arr);

char	*get_path(char **envp, char *cmd);

#endif