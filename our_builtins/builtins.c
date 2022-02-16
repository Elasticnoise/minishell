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
int 	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
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
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
//		exit(126);
	return (0);
}

void	do_builtins(t_token *token, char **env, t_env **n_env)
{
//	if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
//		signal_exit_status = ft_cd(token, env);
//	else if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
//		signal_exit_status = ft_pwd(token);
	if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
		ft_echo(token);
//	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
//		signal_exit_status = ft_env(token, env);
	else if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
		ft_exit(token, n_env);
//	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
//		signal_exit_status = ft_unset(token, env);
//	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
//		signal_exit_status = ft_export(token, env);
}

int 	ft_echo(t_token *token)
{
	int	i;
	int is_n;

	i = 1;
	is_n = 0;
	while (token->cmd[i] && !ft_strcmp(token->cmd[i], "-n"))
	{
		is_n = 1;
		i++;
	}
	while (token->cmd[i] != NULL)
	{
		ft_putstr_fd(token->cmd[i], 1);
		if (token->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!is_n)
		write(1, "\n", 1);
	return (0);
}

//int	ft_echo(t_token *token)
//{
//	int	i;
//	int	n;
////	int	size;
//
//	i = 1;
//	n = 0;
////	size = 0;
////	while (token->cmd[size])
////		size++;
//	if (token->cmd[1] && !ft_strcmp(token->cmd[2], "-n"))
//	{
//		n = 1;
//		i++;
//	}
//	while (token->cmd[i] != NULL)
//	{
//		ft_putstr_fd(token->cmd[i], 1);
//		if (token->cmd[i + 1] != NULL)
//			write(1, " ", 1);
//		i++;
//	}
//	if (n == 0)
//		write(1, "\n", 1);
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

int	get_shlvl(t_env **n_env)
{
	t_env	*tmp;
	int		lvl;

	tmp = *n_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 6))
		{
			lvl = ft_atoi(tmp->data);
			break;
		}
		tmp = tmp->next;
	}
	return (lvl);
}

//int 	main(int argc, char **argv, char **envp)
//{
//	(void) argc;
//	(void) argv;
////	ft_pwd(envp);
//	return (0);
//}
