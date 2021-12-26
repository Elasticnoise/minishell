/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:35:36 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_pow(unsigned long int value, int base)
{
	unsigned int	count;

	count = 0;
	while (value)
	{
		value = value / base;
		count++;
	}
	return (count);
}

char	*ft_conver_low(unsigned long int value, int base, int reg, int i)
{
	char	*nbr;

	nbr = (char *)malloc(sizeof(nbr) * (i + 1));
	nbr[i] = '\0';
	while (i-- >= 0)
	{
		if (reg == 0)
		{	
			if (value % base > 9)
				nbr[i] = "0123456789abcdef"[(value % base)];
			else
				nbr[i] = "0123456789abcdef"[value % base];
			value = value / base;
		}
		else
		{
			if (value % base > 9)
				nbr[i] = "0123456789ABCDEF"[(value % base)];
			else
				nbr[i] = "0123456789ABCDEF"[value % base];
			value = value / base;
		}
	}
	return (nbr);
}

char	*ft_itoa_base(unsigned long int value, int base, int reg)
{
	char	*nbr;
	int		i;

	if (value == 0)
	{
		nbr = (char *)malloc(sizeof(nbr) * 2);
		nbr[1] = '\0';
		nbr[0] = '0';
		return (nbr);
	}
	i = ft_pow(value, base);
	return (ft_conver_low(value, base, reg, i));
}
