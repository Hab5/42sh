/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:37:56 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:46:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		large_min_convert(t_printf **lst, int len_str, int stock[3])
{
	int		i;
	int		len;
	char	c;
	char	*tmp;

	len = (*lst)->large_min - len_str;
	if (len > 0)
	{
		i = -1;
		if (!(tmp = (char*)malloc(sizeof(char) * len + 1)))
			return ;
		c = ft_strchr_exist((*lst)->options, '0') && (*lst)->precision == -2 &&
			stock[1] == 0 ? '0' : ' ';
		while (++i < len)
			tmp[i] = c;
		tmp[i] = '\0';
		ft_display(tmp, &(*lst));
		ft_strdel(&tmp);
	}
}

void		apply_hash(t_printf **lst)
{
	if (ft_strchr_exist((*lst)->conversion, 'p'))
		apply_hash_p(&(*lst));
	else if (ft_strchr_exist((*lst)->options, '#'))
	{
		if (ft_toupper((*lst)->flag) == 'X')
		{
			(*lst)->len += 2;
			((*lst)->flag == 'x') ? ft_putstr("0x") : ft_putstr("0X");
		}
		else
		{
			(*lst)->len += 1;
			ft_putstr("0");
		}
	}
}

void		apply_hash_p(t_printf **lst)
{
	(*lst)->len += 2;
	ft_putstr("0x");
}

void		apply_arg_convert(char *str, t_printf **lst)
{
	char	*tmp;
	int		len_str;
	int		stock[3];

	ft_stock(&(*lst), str, &stock);
	if (ft_strchr_exist((*lst)->options, '#'))
	{
		(*lst)->large_min -= (ft_toupper((*lst)->flag) == 'X') ? 2 : 1;
		if ((*lst)->precision > 0)
			(*lst)->precision -= ((*lst)->flag == 'o') ? 1 : 0;
	}
	tmp = precision_n(str, &(*lst), 0);
	(stock[1] == 1) ? apply_hash(&(*lst)) : 0;
	(stock[1] == 1) ? ft_display(tmp, &(*lst)) : 0;
	len_str = ft_strlen(tmp);
	(stock[1] == 0 && ft_strchr_exist((*lst)->options, '0') &&
	(*lst)->precision == -2) ? apply_hash(&(*lst)) : 0;
	large_min_convert(&(*lst), len_str, stock);
	(stock[1] == 0 && (ft_strchr_exist((*lst)->options, '0') == 0 ||
		(ft_strchr_exist((*lst)->options, '0') && (*lst)->precision != -2))) ?
		apply_hash(&(*lst)) : 0;
	(stock[1] == 0) ? ft_display(tmp, &(*lst)) : 0;
	ft_strdel(&tmp);
}
