/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:35:50 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	i = 0;
	dest = (unsigned char *) dst;
	source = (unsigned char *) src;
	while (i < n)
	{	
		dest[i] = source[i];
		dst++;
		if (source[i] == (unsigned char) c)
			return (dst);
		i++;
	}
	return (0);
}
