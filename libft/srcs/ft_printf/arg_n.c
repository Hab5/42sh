/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:06:43 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/22 10:36:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conversion(char **str, t_printf **lst)
{
	if ((*lst)->conversion[0] == 'h')
	{
		if ((*lst)->conversion[1] == 'h')
			(*str) = ft_itoa_sc((signed char)va_arg((*lst)->ap, int));
		else
			(*str) = ft_itoa_s((short)va_arg((*lst)->ap, int));
	}
	else if ((*lst)->conversion[0] == 'l')
		(*str) = ft_itoa_long(va_arg((*lst)->ap, long long));
	else
		(*str) = ft_itoa(va_arg((*lst)->ap, int));
	if (ft_strcmp(*str, "\0") == 0)
		(*str) = ft_strdup("0\0");
}

void	ft_arg_d(t_printf **lst)
{
	char	*str;

	ft_conversion(&str, &(*lst));
	apply_arg_n(str, &(*lst));
	ft_strdel(&str);
}

void	ft_conversion_u(char **str, t_printf **lst)
{
	if ((*lst)->conversion[0] == 'h')
	{
		if ((*lst)->conversion[1] == 'h')
			(*str) = ft_itoa((int)((unsigned char)va_arg((*lst)->ap, int)));
		else
			(*str) = ft_itoa_us((unsigned short)va_arg((*lst)->ap, int));
	}
	else if ((*lst)->conversion[0] == 'l')
		(*str) = ft_itoa_ul(va_arg((*lst)->ap, unsigned long long));
	else
		(*str) = ft_itoa_ul(va_arg((*lst)->ap, unsigned int));
}

void	ft_arg_u(t_printf **lst)
{
	char	*str;
	int		find;

	find = ft_chr_index((*lst)->options, '+');
	(find != -1) ? (*lst)->options[find] = 'N' : 0;
	find = ft_chr_index((*lst)->options, ' ');
	(find != -1) ? (*lst)->options[find] = 'N' : 0;
	ft_conversion_u(&str, &(*lst));
	if (str && ft_strcmp(str, "") == 0)
	{
		ft_strdel(&str);
		str = ft_strdup("0");
	}
	apply_arg_n(str, &(*lst));
	ft_strdel(&str);
}
