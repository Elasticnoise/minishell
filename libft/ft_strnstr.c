/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:03:59 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	start;
	unsigned int	i;

	if (!*needle)
		return ((char *)haystack);
	start = 0;
	while (haystack[start] != '\0' && (size_t)start < len)
	{
		if (haystack[start] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' && haystack[start + i] == needle[i]
				&& (size_t)(start + i) < len)
				++i;
			if (needle[i] == '\0')
				return ((char *)&haystack[start]);
		}
		++start;
	}
	return (0);
}
