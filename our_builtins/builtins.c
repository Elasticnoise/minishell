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

/* TODO 1) to split builtins for owns files. 2) export, unset, cd, exit need to developed */
/* TODO 2) При исполнении $, нужно проверять текст выводимого значения и если нужно исполнять команды"
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

int 	ft_pwd(t_main *main)
{
	printf("%s\n", get_right_env(env, "PWD"));
	return (0);
}

int 	ft_export(char **env)
{
	return (0);
}

int 	ft_unset(char **env)
{
	return (0);
}

void 	ft_env(t_main *main)
{
	int i;

	i = 0;
	if (main->argc != 1)
	{
		ft_putstr_fd("env: ‘", param->argv[1], "’: Permission denied\n", 2);
		return ;
	}
	while (main->envp[i])
	{
		ft_putstr_fd(param->envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

int 	ft_cd(char **env)
{
	return (0);
}

int check_exit_status(t_main *main)
{
	return (0);
}


int 	ft_exit(t_main *main)
{
	printf("exit\n");

}

int 	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
//	ft_pwd(envp);
	return (0);
}
