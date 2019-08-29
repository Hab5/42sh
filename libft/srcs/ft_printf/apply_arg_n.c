/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:02:59 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:47:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		options_n(t_printf **lst, int stock[3], int neg, int rd)
{
	char	c;
	int		space;

	c = 0;
	(neg) ? stock[0] = 0 : 0;
	space = (neg || stock[0]) ? 0 : ft_strchr_exist((*lst)->options, ' ');
	(space == 1) ? c = ' ' : 0;
	(stock[0]) ? c = '+' : 0;
	(neg) ? c = '-' : 0;
	if (c != 0 && rd == 1)
	{
		(*lst)->len += 1;
		write(1, &c, 1);
	}
}

char		*precision_n(char *str, t_printf **lst, int neg)
{
	int		len[2];
	char	*tmp;
	char	*tmp_b;
	char	*dst;

	if (!(dst = (neg) ? ft_strsub(str, 1, ft_strlen(str)) : ft_strdup(str)))
		return (NULL);
	((dst[0] == '0') && ((*lst)->precision == -1 || (*lst)->precision == 0)) ?
		dst[0] = '\0' : 0;
	len[1] = (*lst)->precision - ft_strlen(dst);
	if (len[1] > 0)
	{
		len[0] = -1;
		if (!(tmp_b = (char*)malloc(sizeof(char) * len[1] + 1)))
			return (NULL);
		while (++len[0] < len[1])
			tmp_b[len[0]] = '0';
		tmp_b[len[0]] = '\0';
		tmp = ft_strjoin(tmp_b, dst);
		ft_strdel(&tmp_b);
	}
	else
		tmp = ft_strdup(dst);
	ft_strdel(&dst);
	return (tmp);
}

void		large_min_n(t_printf **lst, int len_str, int stock[3])
{
	int		i;
	int		len;
	char	c;
	char	*tmp;

	len = (*lst)->large_min - len_str;
	if (len > 0)
	{
		i = -1;
		c = ft_strchr_exist((*lst)->options, '0') && stock[1] == 0 &&
			(*lst)->precision == -2 ? '0' : ' ';
		if (!(tmp = (char*)malloc(sizeof(char) * len + 1)))
			return ;
		while (++i < len)
			tmp[i] = c;
		tmp[i] = '\0';
		ft_display(tmp, &(*lst));
		ft_strdel(&tmp);
	}
}

int			add_length(t_printf **lst, int neg, int stock[3], int len_str)
{
	if (neg || stock[0] || ft_strchr_exist((*lst)->options, ' '))
		len_str += 1;
	return (len_str);
}

void		apply_arg_n(char *str, t_printf **lst)
{
	char	*tmp;
	int		len_str;
	int		neg;
	int		stock[3];

	neg = ft_strchr_exist(str, '-');
	(neg) ? stock[0] = 0 : 0;
	ft_stock(&(*lst), str, &stock);
	(stock[1] == 1) ? options_n(&(*lst), stock, neg, 1) : 1;
	tmp = precision_n(str, &(*lst), neg);
	(stock[1] == 1) ? ft_display(tmp, &(*lst)) : 0;
	len_str = ft_strlen(tmp);
	len_str = add_length(&(*lst), neg, stock, len_str);
	if (stock[1] == 0 && ft_strchr_exist((*lst)->options, '0') &&
			(*lst)->precision == -2)
		options_n(&(*lst), stock, neg, 1);
	large_min_n(&(*lst), len_str, stock);
	(stock[1] == 0 && (ft_strchr_exist((*lst)->options, '0') == 0 ||
		(ft_strchr_exist((*lst)->options, '0') && (*lst)->precision != -2))) ?
		options_n(&(*lst), stock, neg, 1) : 1;
	(stock[1] == 0) ? ft_display(tmp, &(*lst)) : 0;
	ft_strdel(&tmp);
}
