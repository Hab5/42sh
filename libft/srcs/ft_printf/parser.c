/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:41:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:50:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	recup_char(t_printf **lst, int n)
{
	if (n > 0)
		(*lst)->index += n;
	return ((*lst)->format[(*lst)->index]);
}

void	options(t_printf **lst)
{
	int		i;
	char	c;

	i = 0;
	c = (*lst)->format[(*lst)->index];
	while (c)
	{
		if (c == '0' || c == '+' || c == '-' || c == '#' || c == ' ')
		{
			if (ft_strchr_exist((*lst)->options, c) != -1)
				(*lst)->options[i++] = c;
		}
		else
			break ;
		c = (*lst)->format[++(*lst)->index];
	}
}

void	other_options(t_printf **lst)
{
	if (ft_isdigit(recup_char(&(*lst), 0)))
	{
		(*lst)->large_min = ft_atoi((*lst)->format + (*lst)->index);
		(*lst)->index += ft_numlen((*lst)->large_min);
	}
	if (recup_char(&(*lst), 0) == '.')
	{
		if (ft_isdigit(recup_char(&(*lst), 1)))
		{
			(*lst)->precision = ft_atoi((*lst)->format + (*lst)->index);
			while ((*lst)->precision != 0 &&
					(*lst)->format[(*lst)->index] == '0')
				(*lst)->index++;
			(*lst)->index += ft_numlen((*lst)->precision);
		}
		else
			(*lst)->precision = -1;
	}
}

void	search_conversion(t_printf **lst)
{
	int	i;

	i = -1;
	if ((*lst)->format[(*lst)->index] == 'h')
	{
		(*lst)->conversion[++i] = 'h';
		if ((*lst)->format[(*lst)->index + 1] == 'h')
			(*lst)->conversion[++i] = 'h';
	}
	else
	{
		if ((*lst)->format[(*lst)->index] == 'l')
		{
			(*lst)->conversion[++i] = 'l';
			if ((*lst)->format[(*lst)->index + 1] == 'l')
				(*lst)->conversion[++i] = 'l';
		}
	}
	(*lst)->index += ft_strlen((*lst)->conversion);
	(*lst)->flag = recup_char(&(*lst), 0);
}

void	ft_manage(t_printf **lst)
{
	(*lst)->index++;
	options(&(*lst));
	other_options(&(*lst));
	search_conversion(&(*lst));
	ft_gest_flag(&(*lst));
}
