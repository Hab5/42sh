/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:52:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:47:11 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*precision_s(char *str, t_printf **lst)
{
	char	*tmp;

	if ((*lst)->precision == -1)
		tmp = ft_strdup("\0");
	else if ((*lst)->precision != -2 && (*lst)->precision < (int)ft_strlen(str))
		tmp = ft_strsub(str, 0, (*lst)->precision);
	else
		tmp = ft_strdup(str);
	return (tmp);
}

void		large_min_s(t_printf **lst, int len_str)
{
	int		i;
	char	c;
	int		len;
	char	*tmp;

	len = (*lst)->large_min - len_str;
	if (len > 0)
	{
		i = -1;
		if (!(tmp = (char*)malloc(sizeof(char) * len + 1)))
			return ;
		c = ft_strchr_exist((*lst)->options, '0') &&
			ft_strchr_exist((*lst)->options, '-') == 0 ? '0' : ' ';
		while (++i < len)
			tmp[i] = c;
		tmp[i] = '\0';
		ft_display(tmp, &(*lst));
		ft_strdel(&tmp);
	}
}

void		apply_arg_s(char *str, t_printf **lst)
{
	int		stock[3];
	char	*tmp;
	int		len_str;

	ft_stock(&(*lst), str, &stock);
	tmp = precision_s(str, &(*lst));
	(stock[1] == 1) ? ft_display(tmp, &(*lst)) : 0;
	len_str = ft_strlen(tmp);
	large_min_s(&(*lst), len_str);
	(stock[1] == 0) ? ft_display(tmp, &(*lst)) : 0;
	ft_strdel(&tmp);
}

void		apply_arg_c(char c, t_printf **lst)
{
	char	*str;
	int		stock[3];
	int		len_str;

	if (!(str = (char*)malloc(sizeof(char) + 2)))
		return ;
	str[0] = c;
	str[1] = '\0';
	ft_stock(&(*lst), str, &stock);
	(stock[1] == 1 && c != 0) ? ft_display(str, &(*lst)) : 0;
	(stock[1] == 1 && c == 0) ? write(1, &c, 1) : 0;
	len_str = ft_strlen(str);
	len_str == 0 ? len_str = 1 : 0;
	large_min_s(&(*lst), len_str);
	(stock[1] == 0 && c != 0) ? ft_display(str, &(*lst)) : 0;
	(stock[1] == 0 && c == 0) ? write(1, &c, 1) : 0;
	ft_strdel(&str);
}
