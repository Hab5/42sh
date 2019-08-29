/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:44:12 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 13:35:33 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	ptrdst = (unsigned char*)dst;
	ptrsrc = (unsigned char*)src;
	i = 0;
	if (dst < src)
		while (i < len)
		{
			ptrdst[i] = ptrsrc[i];
			++i;
		}
	else
		while (len > i)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
	return (dst);
}
