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
//	if (ft_strncmp(cmd, "echo", 5) == 0)
//		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
//	if (ft_strncmp(cmd, "pwd", 4) == 0)
//		return (3);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
//		exit(126);
	return (0);
}

int	ft_check_exit_status(char *str)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		i++;
		sign++;
	}
	while (str && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if ((i - sign) > 19)
		return (-1);
	return (0);
}

int	ft_check_n(long long int n, char c)
{
	long long int	max;
	long long int	min;

	max = 9223372036854775807;
	min = -9223372036854775807;
	if (n > max / 10 || n < min / 10)
		return (-1);
	if (n == (max / 10) && (c == '8' || c == '9'))
		return (-1);
	if (n == (min / 10) && c == '9')
		return (-1);
	return (0);
}

int	ft_exit_status(char *str)
{
	long long int	n;
	int				i;
	int				sign;

	if (str && ft_strncmp("-9223372036854775808", str, ft_strlen(str)) == 0)
		return (0);
	n = 0;
	sign = 1;
	i = 0;
	if (str && str[i] == '-')
		sign = -1;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str && ft_isdigit(str[i]))
	{
		if (ft_check_n(n, str[i]))
			return (-1);
		n = 10 * n + (str[i] - 48) * sign;
		i++;
	}
	n = n % 256;
	while (n < 0)
		n = n + 256;
	return (n);
}

void	ft_exit_err_msg(char *str)
{
	signal_exit_status = 255;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int 	ft_exit(t_token *token, t_env **n_env)
{
	lvl_down(n_env);
	ft_putstr_fd("exit\n", 1);
	if (ft_check_exit_status(token->cmd[1]))
		ft_exit_err_msg(token->cmd[1]);
	else {
		if (token->cmd[1] && token->cmd[2]) {
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		signal_exit_status = ft_exit_status(token->cmd[1]);
		if (signal_exit_status == -1)
			ft_exit_err_msg(token->cmd[1]);
	}
	return (signal_exit_status);
}

void	do_builtins(t_token *token, char **env, t_env **n_env)
{
//	if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
//		signal_exit_status = ft_cd(token, env);
//	else if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
//		signal_exit_status = ft_pwd(token);
//	else if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
//		signal_exit_status = ft_echo(token);
//	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
//		signal_exit_status = ft_env(token, env);
	if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
	{
//		printf("stop!!!\n");
		ft_exit(token, n_env);
	}
//	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
//		signal_exit_status = ft_unset(token, env);
//	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
//		signal_exit_status = ft_export(token, env);
}

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

int	check_exit_status(t_env **env)
{
	if (get_shlvl(env) == 1)
		return (1);
	else
	{
		signal_exit_status = 0;
		return (0);
	}
}

//int 	main(int argc, char **argv, char **envp)
//{
//	(void) argc;
//	(void) argv;
////	ft_pwd(envp);
//	return (0);
//}
