/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:39:03 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:48:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_del_lst(t_printf **lst)
{
	if (*lst)
	{
		ft_strdel(&((*lst)->format));
		free(*lst);
	}
}

int		ft_printf(const char *format, ...)
{
	int			len;
	t_printf	*lst;

	if (ft_prepare(format, &lst) == 0)
		return (0);
	va_start((lst)->ap, format);
	while (lst->format[lst->index])
	{
		if (lst->format[lst->index] == '%')
		{
			ft_reset_value(&lst);
			ft_manage(&lst);
		}
		else
		{
			ft_putchar(lst->format[lst->index]);
			lst->len++;
		}
		lst->index++;
	}
	va_end(lst->ap);
	len = lst->len;
	ft_del_lst(&lst);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	int			len;
	t_printf	*lst;

	if (ft_prepare(format, &lst) == 0)
		return (0);
	lst->fd = fd;
	va_start((lst)->ap, format);
	while (lst->format[lst->index])
	{
		if (lst->format[lst->index] == '%')
		{
			ft_reset_value(&lst);
			ft_manage(&lst);
		}
		else
		{
			ft_putchar_fd(lst->format[lst->index], fd);
			lst->len++;
		}
		lst->index++;
	}
	va_end(lst->ap);
	len = lst->len;
	ft_del_lst(&lst);
	return (len);
}
