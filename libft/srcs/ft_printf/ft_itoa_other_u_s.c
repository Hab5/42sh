/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:19:56 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:48:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_sc(signed char c)
{
	int		nbr;
	int		size;
	int		negatif;
	char	*str;

	negatif = (c < 0) ? 1 : 0;
	nbr = (negatif) ? -(int)c : (int)c;
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

char		*ft_itoa_ul(unsigned long long n)
{
	unsigned long long	nbr;
	int					size;
	char				*str;

	nbr = (unsigned long long)n;
	size = ft_len_unsigned(nbr);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		(str)[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

char		*ft_itoa_us(unsigned short n)
{
	int		nbr;
	int		size;
	char	*str;

	nbr = (int)n;
	size = ft_numlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}
