/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:30:54 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 10:48:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_startjoin(char (*str)[BUF_S], char c)
{
	int		len;

	len = ft_strlen(*str);
	if (len == BUF_S)
		return ;
	while (--len >= 0)
		(*str)[len + 1] = (*str)[len];
	(*str)[0] = c;
}

void		ft_convert_base(unsigned int nb, int base, char (*str)[BUF_S])
{
	unsigned int	result;
	char			c;

	ft_bzero(&(*str), BUF_S);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_uc(unsigned char nb, int base, char (*str)[BUF_S])
{
	unsigned char	result;
	char			c;

	ft_bzero(&(*str), BUF_S);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_us(unsigned short nb, int base, char (*str)[BUF_S])
{
	unsigned short	result;
	char			c;

	ft_bzero(&(*str), BUF_S);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_ll(unsigned long long nb, int base,
		char (*str)[BUF_S])
{
	unsigned long long	result;
	char				c;

	ft_bzero(&(*str), BUF_S);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}
