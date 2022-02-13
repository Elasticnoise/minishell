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
/* TODO 2) При исполнении $, нужно проверять текст выводимого значения и если нужно исполнять команды" */
//int 	is_builtin(char *cmd)
//{
//	if (ft_strncmp(cmd, "echo", 5) == 0)
//		return (1);
//	if (ft_strncmp(cmd, "cd", 3) == 0)
//		return (2);
//	if (ft_strncmp(cmd, "pwd", 4) == 0)
//		return (3);
//	if (ft_strncmp(cmd, "export", 7) == 0)
//		return (4);
//	if (ft_strncmp(cmd, "unset", 6) == 0)
//		return (5);
//	if (ft_strncmp(cmd, "env", 4) == 0)
//		return (6);
//	if (ft_strncmp(cmd, "exit", 5) == 0)
//		return (7);
//	return (0);
//}

//void do_builtins(t_token *token, t_env **env)
//{
//	if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
//		signal_exit_status = ft_cd(token, env);
//	else if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
//		signal_exit_status = ft_pwd(token);
//	else if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
//		signal_exit_status = ft_echo(token);
//	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
//		signal_exit_status = ft_env(token, env);
//	else if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
//		signal_exit_status = ft_exit(token);
//	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
//		signal_exit_status = ft_unset(token, env);
//	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
//		signal_exit_status = ft_export(token, env);
//}

//int 	ft_echo(t_main *main)
//{
//	int	i;
//	int is_n;
//
//	i = 1;
//	is_n = 0;
//	if (main->cmd[2] && ft_strncmp(main->cmd[2], "-n", 3) == 0)
//	{
//		is_n = 1;
//		i++;
//	}
//	while (main->cmd[i] != NULL)
//	{
//		ft_putstr_fd(main->cmd[i], 1);
//		i++;
//	}
//	if (is_n)
//		write(1, "\n", 1);
//
//	return (0);
//}

//int 	ft_pwd(t_main *main)
//{
//	printf("%s\n", do_(env, "PWD"));
//	return (0);
//}

int 	ft_export(char **env)
{
	return (0);
}

int 	ft_unset(char **env)
{
	return (0);
}

//void 	ft_env(t_main *main)
//{
//	int i;
//
//	i = 0;
//	if (main->argc != 1)
//	{
//		ft_putstr_fd("env: ‘", param->argv[1], "’: Permission denied\n", 2);
//		return ;
//	}
//	while (main->envp[i])
//	{
//		ft_putstr_fd(param->envp[i], 1);
//		write(1, "\n", 1);
//		i++;
//	}
//}

int 	ft_cd(char **env)
{
	return (0);
}

int check_exit_status(t_main *main)
{
	return (0);
}


//int 	ft_exit(t_main *token)
//{
//
//	mini->exit = 1;
//	ft_putstr_fd("exit ", STDERR);
//	cmd[1] ? ft_putendl_fd("❤️", STDERR) : ft_putendl_fd("💚", STDERR);
//	if (cmd[1] && cmd[2])
//	{
//		mini->ret = 1;
//		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
//	}
//	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
//	{
//		mini->ret = 255;
//		ft_putstr_fd("minishell: exit: ", STDERR);
//		ft_putstr_fd(cmd[1], STDERR);
//		ft_putendl_fd(": numeric argument required", STDERR);
//	}
//	else if (cmd[1])
//		mini->ret = ft_atoi(cmd[1]);
//	else
//		mini->ret = 0;
//}

//int 	main(int argc, char **argv, char **envp)
//{
//	(void) argc;
//	(void) argv;
////	ft_pwd(envp);
//	return (0);
//}
