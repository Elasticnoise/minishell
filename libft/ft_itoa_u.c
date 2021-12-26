/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <lechalme@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:36:00 by lechalme          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:30 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_write_to_buf(unsigned int nbr, int i, char *buf, int minus)
{
	char	word;
	int		g;

	g = i;
	if (nbr < 0)
		nbr *= (-1);
	if (nbr == 0)
	{
		word = nbr % 10 + '0';
		i--;
	}
	if (i == -1)
		buf[0] = '0';
	while (nbr)
	{
		i--;
		word = nbr % 10 + '0';
		buf[i] = word;
		nbr = nbr / 10;
	}
	if (word == '0' && g == 1)
		buf[i] = '0';
	i--;
	if (i == 0 && minus == 1)
		buf[i] = '-';
}

static void	ft_pos_or_neg(unsigned int *n, int *len, int *minus)
{
	int		l;
	long	nb;
	int		min;

	l = *len;
	nb = *n;
	min = *minus;
	if (nb < 0 && ++l && ++min)
		nb *= (-1);
	while (nb > 0)
	{
		nb /= 10;
		l++;
	}
	if (l == 0)
		l++;
	if (minus)
		*n = 4294967295 - nb;
	else
		*n = nb;
	*len = l;
	*minus = min;
}

char	*ft_itoa_u(unsigned int n)
{
	int				i;
	int				len;
	long			nbr;
	char			*buf;
	int				minus;

	i = 0;
	minus = 0;
	len = 0;
	if (n < 0)
	{
		n *= (-1);
	}
	nbr = (unsigned int) n;
	ft_pos_or_neg(&n, &len, &minus);
	i = len;
	if (i == (-1))
		len--;
	buf = (char *)malloc(sizeof(char) * (len) + 1);
	if (!buf)
		return (NULL);
	ft_write_to_buf(nbr, i, buf, minus);
	buf[len] = '\0';
	return (buf);
}
