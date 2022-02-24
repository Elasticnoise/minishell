/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:52:13 by ghanh             #+#    #+#             */
/*   Updated: 2022/02/24 18:52:15 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_help(t_env **env, char *new)
{
	t_env	*help;

	help = *env;
	while (help)
	{
		if (!ft_strcmp(help->name, new))
		{
			free(new);
			break ;
		}
		help = help->next;
	}
	return (help);
}
