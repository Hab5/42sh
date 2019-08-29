/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:39:03 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:50:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_blank_list(t_printf **lst)
{
	if (!((*lst) = (t_printf*)malloc(sizeof(t_printf) * 1)))
		return ;
	ft_bzero(&(*lst)->options, 50);
	ft_bzero(&(*lst)->conversion, 3);
	(*lst)->large_min = 0;
	(*lst)->precision = -2;
	(*lst)->flag = '0';
	(*lst)->value = 0;
	(*lst)->len = 0;
	(*lst)->index = 0;
	(*lst)->fd = 1;
	(*lst)->color = 0;
}

void	ft_reset_value(t_printf **lst)
{
	ft_bzero(&(*lst)->options, 50);
	ft_bzero(&(*lst)->conversion, 3);
	(*lst)->large_min = 0;
	(*lst)->precision = -2;
	(*lst)->flag = '0';
	(*lst)->value = 0;
}

char	*insert_format(const char *e)
{
	int		i;
	char	*format;

	i = -1;
	format = (char*)malloc(sizeof(char) * ft_strlen(e) + 1);
	while (e[++i])
		format[i] = e[i];
	format[i] = '\0';
	return (format);
}

int		ft_prepare(const char *format, t_printf **lst)
{
	if (!format)
		return (0);
	ft_blank_list(&(*lst));
	(*lst)->format = insert_format(format);
	return (1);
}
