/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:04:06 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	stop;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	stop = ft_strlen(s1);
	while (s1[j] != '\0' && ft_char_in_set(s1[j], set) == 1)
		j++;
	while (stop > j && ft_char_in_set(s1[stop - 1], set) == 1)
		stop--;
	str = (char *)malloc(sizeof(char) * (stop - j + 1));
	if (!str)
		return (NULL);
	while (j < stop)
	{
		str[i] = s1[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
