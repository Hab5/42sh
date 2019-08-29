/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:41:32 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/22 10:37:24 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_type(t_printf **lst, char (*str)[BUF_S], int base)
{
	if ((*lst)->conversion[0] == 'h')
	{
		if ((*lst)->conversion[1] == 'h')
			ft_convert_base_uc((unsigned char)va_arg((*lst)->ap, int), base,
					&(*str));
		else
			ft_convert_base_us((unsigned short)va_arg((*lst)->ap, int), base,
					&(*str));
	}
	else if ((*lst)->conversion[0] == 'l')
		ft_convert_base_ll(va_arg((*lst)->ap, long long), base, &(*str));
	else
		ft_convert_base(va_arg((*lst)->ap, int), base, &(*str));
}

void		convert_to(t_printf **lst, int base)
{
	int		i;
	int		index_hash;
	char	str[BUF_S];

	i = -1;
	convert_type(&(*lst), &str, base);
	if (str[0] == '\0')
		result_null(&(*lst), &str);
	else
	{
		if ((*lst)->flag == 'x')
			while (str[++i])
				str[i] = ft_tolower(str[i]);
	}
	index_hash = ft_chr_index((*lst)->options, '#');
	if ((ft_strcmp(str, "0") == 0 || ft_strcmp(str, "") == 0) &&
			index_hash > -1 && ft_strchr_exist((*lst)->conversion, 'p') == 0)
		(*lst)->options[index_hash] = 'N';
	apply_arg_convert(str, &(*lst));
}

void		ft_arg_pointer(t_printf **lst)
{
	(*lst)->flag = 'x';
	ft_startjoin_50(&(*lst)->options, '#');
	(*lst)->conversion[0] = 'l';
	(*lst)->conversion[1] = 'p';
	ft_arg_x(&(*lst));
}

void		ft_arg_x(t_printf **lst)
{
	convert_to(&(*lst), 16);
}

void		ft_arg_o(t_printf **lst)
{
	int		find;

	find = ft_chr_index((*lst)->options, '+');
	(find != -1) ? (*lst)->options[find] = 'N' : 0;
	convert_to(&(*lst), 8);
}
