#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

void	child_proc(int *pipe_fd, char **av, char **envp)
{
	char **cmd;
	int in_file;


	cmd = ft_split(av[2], ' ');
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	in_file = open(av[1], O_RDONLY);
	dup2(in_file, 0);
	if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
}

void 	master_proc(int **pipe_fd, int i, char **av, char **envp)
{
	char **cmd;
	int out_file;

	out_file = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 777);
	wait (0);
	close(pipe_fd[i][1]);
	cmd = ft_split(av[3], ' ');
	dup2(pipe_fd[i][0], 0);
	close(pipe_fd[i][0]);
	dup2(out_file, 1);
	if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
}

int		main(int ac, char **av, char **envp)
{
	int		i;
	int		**pipe_fd;
	int		command;
	int		num_cmd;
	pid_t	pid;
	int		j;
	char **cmd;

	num_cmd = ac - 3;
	i = 0;
	command = 0;
	pipe_fd = malloc(sizeof(int*) * (ac - 3));
	/* init pipes */
	while (i < (ac -3))
	{
		pipe_fd[i] = malloc(sizeof(int*) * 2);
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe error");
			exit(0);
		}
		i++;
	}
	i = 0;
	while (command < num_cmd)
	{
		pid = fork();
		if (i == 0)
		{
			child_proc(pipe_fd[i], av, envp);
			i++;
		}
		if (pid == 0)
		{
			if (i > 0)
			{
				if (dup2(pipe_fd[i][0], 0) == -1)
				{
					perror("dup2 input error");
					exit(0);
				}
				if (i != num_cmd -1)
				{
					if (dup2(pipe_fd[i][1], 1) == -1)
					{
						perror("dup2 output error");
						exit(0);
					}
				}
				close(pipe_fd[i][1]);
				close(pipe_fd[i][0]);
				cmd = ft_split(av[i + 2], ' ');
				if (execve(get_path(envp, cmd[0]), cmd, envp) == -1)
				{
					perror("pipex: command not found: ");
					exit(0);
				}
				free(cmd);
				i++;
			}
		}
		else if (pid < 0)
		{
			perror("incorrect pid");
			exit (0);
		}
		command++;
	}
	master_proc(pipe_fd, ac, av, envp);
	i = 0;
	while (i < 2 * (num_cmd - 1))
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
	return (0);
}
