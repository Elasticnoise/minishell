/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:48:33 by lechalme          #+#    #+#             */
/*   Updated: 2022/02/25 20:48:35 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_list(t_token **head)
{
	t_token	*tmp;
	int		i;

	while (*head)
	{
		i = 0;
		tmp = (*head)->next;
		if ((*head)->infile)
			free((*head)->infile);
		if ((*head)->outfile)
			free((*head)->outfile);
		if ((*head)->limiter)
			free((*head)->limiter);
		if ((*head)->cmd)
		{
			while ((*head)->cmd[i])
			{
				free((*head)->cmd[i]);
				i++;
			}
			free((*head)->cmd);
		}
		free(*head);
		*head = tmp;
	}
}

void	ft_clean(t_token **token, char	**new_env, t_env **n_env)
{
	free_doublechar(new_env);
	unlink(".tmp_file");
	free_list(token);
	if (check_exit_status(n_env))
		exit(g_exit_status);
}
