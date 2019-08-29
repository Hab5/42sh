/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:48:33 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_len_unsigned(unsigned long long n)
{
	int		cnt;

	cnt = 0;
	while (n != 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

int			ft_len_long(long long n)
{
	int		cnt;

	cnt = 0;
	while (n != 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

char		*ft_itoa_long(long long n)
{
	unsigned long long	nbr;
	int					size;
	int					negatif;
	char				*str;

	negatif = (n < 0) ? 1 : 0;
	nbr = (negatif) ? -(long long)n : (long long)n;
	size = ft_len_long(nbr) + negatif;
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	(negatif) ? str[0] = '-' : 0;
	str[ft_strlen(str)] = '\0';
	return (str);
}

char		*ft_itoa_s(short n)
{
	int		nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = (n < 0) ? 1 : 0;
	nbr = (negatif) ? -(int)n : (int)n;
	size = ft_numlen(nbr) + negatif;
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	(negatif) ? str[0] = '-' : 0;
	str[ft_strlen(str)] = '\0';
	return (str);
}
