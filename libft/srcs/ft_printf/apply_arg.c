/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 08:49:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:46:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_large_min(char (*dst)[BUF_S], t_printf *lst, int stock[3])
{
	char	c;
	int		i;
	char	tmp[BUF_S];

	i = -1;
	c = (ft_strchr_exist(lst->options, '0') && lst->precision < 0) ? '0' : ' ';
	if (ft_strcmp(*dst, "0\0") == 0 && ft_strchr_exist(lst->options, '0') == 0
			&& (lst->large_min == 0 || (lst->precision == -1 ||
					lst->precision == 0)))
		ft_bzero(&(*dst), BUF_S);
	if (stock[2] > 0)
	{
		if (ft_strchr_exist(lst->options, '-'))
			while (stock[2]-- > 0)
				(*dst)[ft_strlen(*dst) + stock[2]] = ' ';
		else
		{
			while (stock[2] > ++i)
				tmp[i] = c;
			i = 0;
			while (stock[2] < BUF_S)
				tmp[stock[2]++] = (*dst)[i++];
			ft_cpy_str(&(*dst), tmp);
		}
	}
}

/*
**	stock[0] = plus
**	stock[1] = moins
**	stock[2] = len
*/
