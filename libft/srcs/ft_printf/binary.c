/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 09:00:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:48:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_see_binary(int nb)
{
	char	c;

	c = '0';
	if (nb > 0)
	{
		c = (nb & 1) + '0';
		if ((nb >> 1) != 0)
			ft_see_binary(nb >> 1);
		write(1, &c, 1);
	}
	else if (nb == 0)
		write(1, &c, 1);
}

void	ft_see_binary_u64(t_u64 nb)
{
	char	c;

	c = '0';
	if (nb > 0)
	{
		c = (nb & 1) + '0';
		if ((nb >> 1) != 0)
			ft_see_binary(nb >> 1);
		write(1, &c, 1);
	}
	else if (nb == 0)
		write(1, &c, 1);
}

char	ft_binary_to_char(t_u64 nb)
{
	char	c;

	c = '0';
	if (nb > 0)
		c = (nb & 1) + '0';
	return (c);
}
