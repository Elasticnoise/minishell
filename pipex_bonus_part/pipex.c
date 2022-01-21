#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

void	do_exec(char **av, char **envp, int i)
{
	char	**cmd;

	cmd = ft_split(av[i], ' ');

	if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd("\n", 2);
		free(cmd);
		exit(0);
	}
	free(cmd);
}

int	ft_redirect(char **av, char **env, int in_file, int out_file, int i)
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
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT);
		do_exec(av, env, i);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int 	in_file;
	int 	out_file;
	int 	i;

	i = 3;

	if (ac >= 5)
	{
		in_file = open(av[1], INFILE);
		out_file = open(av[ac - 1], OUTFILE);
		dup2(in_file, INFILE);
		dup2(out_file, OUTFILE);
		ft_redirect(av, envp, in_file, out_file,2);
		while (i < ac - 2)
			ft_redirect(av, envp, in_file, out_file, i++);
		do_exec(av, envp, i);
	}
	else
	{
		ft_putstr_fd("Usage : ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	return (0);
}
