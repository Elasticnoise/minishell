/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:04:02 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*pointer;
	int		i;

	i = 0;
	pointer = NULL;
	str = (char *) s;
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			pointer = &str[i];
		i++;
	}
	if (str[i] == (char) c)
		return ((char *) &s[i]);
	return (pointer);
}
