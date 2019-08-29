/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:04:15 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/23 12:39:33 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		sign;
	long	nbr;
	long	dup;

	nbr = n;
	sign = 1;
	i = 0;
	if (nbr == 0)
		return (ft_strdup("0"));
	if ((sign = nbr) < 0 && (++i > 0))
		nbr = -nbr;
	dup = nbr * 10;
	while ((dup /= 10) > 0)
		++i;
	if (!(ptr = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ptr[i--] = '\0';
	ptr[i--] = nbr % 10 + 48;
	while ((nbr /= 10) != 0)
		ptr[i--] = nbr % 10 + 48;
	if (sign < 0)
		ptr[i] = '-';
	return (ptr);
}
