/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:05:30 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 20:29:01 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isprime(const int x)
{
	int	i;

	if (x < 2)
		return (-1);
	if (x < 4)
		return (1);
	if ((x % 2) == 0)
		return (0);
	i = 3;
	while (i <= ft_sqrt(x))
	{
		if ((x % i) == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int		ft_nextprime(int x)
{
	while (ft_isprime(x) != 1)
		++x;
	return (x);
}
