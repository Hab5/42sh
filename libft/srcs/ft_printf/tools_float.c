/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:59:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:50:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_inf_nan(char (*str)[BUF_S], t_printf **lst, int stock[3])
{
	int	len;

	len = ft_strlen(*str);
	if ((*str)[len - 1] != 'n' && (*str)[len - 1] != 'f')
		return ;
	ft_large_min(&(*str), (*lst), stock);
}

char	*apply_round_i(char dst[BUF_S], int *i, int precision)
{
	char	*tmp;
	int		cnt;
	int		j;

	j = 0;
	cnt = -1;
	if (!(tmp = (char*)malloc(sizeof(char) * *i + precision + 1)))
		return (NULL);
	while (++cnt < *i)
		tmp[cnt] = dst[cnt];
	while (dst[*i + j] && j <= precision)
		tmp[cnt++] = dst[*i + j++];
	while (j <= precision)
	{
		tmp[cnt++] = '0';
		j++;
	}
	*i += j;
	tmp[cnt] = '\0';
	return (tmp);
}

char	*apply_round_ni(char dst[BUF_S])
{
	char	*tmp;
	int		cnt;

	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(dst) + 1)))
		return (NULL);
	cnt = -1;
	while (dst[++cnt])
		tmp[cnt] = dst[cnt];
	tmp[cnt] = '\0';
	return (tmp);
}

void	apply_round_final(int stock, char **tmp, int i)
{
	while (stock > 0)
	{
		if ((*tmp)[i] != '.')
		{
			stock += (*tmp)[i] - '0';
			(*tmp)[i] = (stock % 10) + '0';
			stock /= 10;
		}
		i--;
	}
}

char	*ft_apply_round(char (*dst)[BUF_S], int stock, int precision)
{
	char	*tmp;
	int		i;

	i = ft_chr_index((*dst), '.');
	if (i != -1)
	{
		if (!(tmp = apply_round_i(*dst, &i, precision)))
			return (NULL);
	}
	else
	{
		if (!(tmp = apply_round_ni(*dst)))
			return (NULL);
	}
	i = (i == -1) ? (int)ft_strlen(*dst) - 1 : i - 1;
	stock = (stock > 4) ? 1 : 0;
	apply_round_final(stock, &tmp, i);
	return (tmp);
}
