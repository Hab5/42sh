/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:18:43 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:50:50 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		ft_alpha(unsigned int nb)
{
	char	c;

	c = 55 + nb;
	return (c);
}

void		ft_startjoin_50(char (*str)[50], char c)
{
	int		len;

	len = ft_strlen(*str);
	if (len == BUF_SIZE)
		return ;
	while (--len >= 0)
		(*str)[len + 1] = (*str)[len];
	(*str)[0] = c;
}

void		result_null(t_printf **lst, char (*str)[BUF_S])
{
	if ((*lst)->precision == -2 || (*lst)->precision > 0 ||
			(ft_strchr_exist((*lst)->options, '#') && (*lst)->flag == 'o') ||
			((*lst)->conversion[1] && (*lst)->conversion[1] == 'p'))
	{
		(*str)[0] = '0';
		if ((*lst)->conversion[1] && (*lst)->conversion[1] == 'p')
		{
			if ((*lst)->precision > 0)
				(*str)[2] = '0';
		}
	}
	if (ft_strchr_exist((*lst)->options, '#') && ((*lst)->precision == -1 ||
			(*lst)->precision == 0) && ft_tolower((*lst)->flag) == 'o')
		(*lst)->precision = -2;
}
