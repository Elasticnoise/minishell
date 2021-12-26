/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:36:19 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
* No math, just do. if src < dst => reverse copy,
* if src > dst => standard, else return(dst)
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *) dst;
	source = (unsigned char *) src;
	i = 0;
	if (source < dest)
	{
		while (i < len--)
			*(dest + len) = *(source + len);
	}
	else
		return (ft_memcpy(dest, source, len));
	return (dst);
}
