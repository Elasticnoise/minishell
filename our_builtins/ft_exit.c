/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:39:16 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 15:39:18 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_exit(t_token *token, t_env **n_env)
{
	lvl_down(n_env);
	ft_putstr_fd("exit\n", 1);
	if (ft_check_exit_status(token->cmd[1]))
		ft_exit_err_msg(token->cmd[1]);
	else
	{
		if (token->cmd[1] && token->cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		g_exit_status = ft_exit_status(token->cmd[1]);
		if (g_exit_status == -1)
			ft_exit_err_msg(token->cmd[1]);
	}
	return (g_exit_status);
}
