/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication_float.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:37:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:03:46 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	tablo_calc(char (*lst)[BUF_S], int base)
{
	int		i;
	int		stock;

	i = ft_strlen(*lst);
	stock = 0;
	while (--i >= 0)
	{
		stock += (((*lst)[i] - '0') * base);
		(*lst)[i] = (stock % 10) + '0';
		if (stock != 0)
		{
			stock /= 10;
			if (i == 0 && stock != 0)
			{
				ft_deplace(&(*lst));
				(*lst)[i] = stock + '0';
			}
		}
	}
}

void	mult_mantissa(char (*lst)[BUF_S], int d)
{
	int	i;

	i = -1;
	while (++i <= d)
		tablo_calc(&(*lst), 2);
}
