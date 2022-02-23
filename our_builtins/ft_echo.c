/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:38:37 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/23 15:38:41 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_echo(t_token *token)
{
	int	i;
	int	is_n;

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
	return (EXIT_SUCCESS);
}
