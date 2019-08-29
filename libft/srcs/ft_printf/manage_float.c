/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:24:41 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:03:09 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** https://ryanstutorials.net/binary-tutorial/binary-floating-point.php
*/

void	div_float(char (*lst)[BUF_S], int d)
{
	int		j;
	int		stock[2];
	char	result[BUF_S];

	if ((*lst)[0] == '0')
		return ;
	d += 1;
	ft_bzero(&(*lst), BUF_S);
	ft_pow_array_fix(d, &result);
	while (--d > 0)
	{
		j = -1;
		stock[1] = 0;
		while (result[++j])
		{
			stock[0] = ((result[j] - '0') * 10) / 2;
			result[j] = ((stock[0] / 10) + stock[1]) + '0';
			stock[1] = stock[0] % 10;
		}
	}
	ft_cpy_str(&(*lst), result);
}

void	manage_mantissa(char (*lst)[BUF_S])
{
	char	result[BUF_S];
	char	tmp[BUF_S];
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(*lst) - 1;
	ft_bzero(&result, BUF_S);
	result[0] = '0';
	while ((*lst)[++i])
	{
		ft_bzero(&tmp, BUF_S);
		tmp[0] = (*lst)[i];
		mult_mantissa(&tmp, --j);
		add_mantissa(&result, tmp);
	}
	ft_bzero(&(*lst), BUF_S);
	ft_cpy_str(&(*lst), result);
}

void	manage_float(char (*lst)[BUF_S])
{
	char	result[BUF_S];
	char	tmp[BUF_S];
	int		i;

	i = -1;
	ft_bzero(&result, BUF_S);
	result[0] = '0';
	while ((*lst)[++i])
	{
		ft_bzero(&tmp, BUF_S);
		tmp[0] = (*lst)[i];
		div_float(&tmp, i);
		add_float(&result, &tmp);
	}
	ft_bzero(&(*lst), BUF_S);
	ft_cpy_str(&(*lst), result);
}

void	ft_gest_float(char (*lst)[BUF_S], int d)
{
	char	mantissa[BUF_S];
	char	float_c[BUF_S];

	d += 1;
	ft_reverse_tablo(&(*lst));
	ft_strsub_tab_fix(&mantissa, (*lst), 0, d);
	if ((int)ft_strlen(mantissa) < d)
		ft_add_zero(&mantissa, d - ft_strlen(mantissa));
	ft_strsub_tab_fix(&float_c, (*lst), d, ft_strlen((*lst)));
	manage_mantissa(&mantissa);
	manage_float(&float_c);
	ft_bzero(&(*lst), BUF_S);
	ft_join(&(*lst), mantissa, 0);
	ft_join(&(*lst), ".\0", 0);
	ft_join(&(*lst), float_c, 0);
}
