/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 10:44:15 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:50:40 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_stock(t_printf **lst, char dst[BUF_S], int (*stock)[3])
{
	(*stock)[0] = ft_strchr_exist((*lst)->options, '+');
	(*stock)[1] = ft_strchr_exist((*lst)->options, '-');
	(*stock)[2] = (*lst)->large_min - ((int)ft_strlen(dst) + (*stock)[0]);
	if (((*lst)->flag == 'd' || (*lst)->flag == 'i') && (*stock)[0])
		(*stock)[2] += ft_strchr_exist(dst, '-');
}

void	ft_cpy_str(char (*dst)[BUF_S], char str[BUF_S])
{
	int	i;

	i = -1;
	while (str[++i])
		(*dst)[i] = str[i];
	while (i < BUF_S)
		(*dst)[i++] = '\0';
}

void	ft_large(char (*buff)[BUF_S], int l, char c)
{
	int		i;

	i = -1;
	while (++i < l)
		(*buff)[i] = c;
	while (i < BUF_S)
		(*buff)[i++] = '\0';
}

void	ft_join(char (*dst)[BUF_S], char *str, int ordre)
{
	int		i;
	int		j;
	char	tmp[BUF_S];

	i = -1;
	j = -1;
	ft_bzero(&tmp, BUF_S);
	if (ordre == 0)
	{
		while ((*dst)[++i])
			tmp[i] = (*dst)[i];
		while (str[++j])
			tmp[i++] = str[j];
	}
	else
	{
		while (str[++i])
			tmp[i] = str[i];
		while ((*dst)[++j])
			tmp[i++] = (*dst)[j];
	}
	ft_cpy_str(&(*dst), tmp);
}
