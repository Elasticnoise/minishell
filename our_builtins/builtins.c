/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 15:37:20 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/26 15:37:23 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int 	is_builtin(t_main *main)
{
	if (ft_strncmp(main->cmd[1], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(main->cmd[1], "cd", 3) == 0)
		return (2);
	if (ft_strncmp(main->cmd[1], "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(main->cmd[1], "export", 7) == 0)
		return (4);
	if (ft_strncmp(main->cmd[1], "unset", 6) == 0)
		return (5);
	if (ft_strncmp(main->cmd[1], "env", 4) == 0)
		return (6);
	if (ft_strncmp(main->cmd[1], "exit", 5) == 0)
		return (7);
	return (0);
}

int 	ft_echo(t_main *main)
{
	int	i;
	int is_n;

	i = 1;
	is_n = 0;
	if (main->cmd[2] && ft_strncmp(main->cmd[2], "-n", 3) == 0)
	{
		is_n = 1;
		i++;
	}
	while (main->cmd[i] != NULL)
	{
		ft_putstr_fd(main->cmd[i], 1);
		i++;
	}
	if (is_n)
		write(1, "\n", 1);

	return (0);
}
char *get_right_env(char **envp, char *right_envp)
{
	int i;
	char *result;

	i = 0;
	while (ft_strnstr(envp[i], right_envp, ft_strlen(envp[i])) == 0)
		i++;
	result = envp[i] + ft_strlen(right_envp ) + 1;
	if (result != NULL)
		return (result);
	return (NULL);
}

int 	ft_pwd(char **env)
{
	printf("%s\n", get_right_env(env, "PWD"));
	return (0);
}

int 	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	ft_pwd(envp);
	return (0);
}
