/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:01:02 by lechalme          #+#    #+#             */
/*   Updated: 2021/12/26 19:01:05 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_right_env(char **envp, char *right_envp)
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


