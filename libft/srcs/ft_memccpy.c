/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:45:07 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 13:33:38 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	i = 0;
	ptrdst = (unsigned char*)dst;
	ptrsrc = (unsigned char*)src;
	while (i < n)
	{
		ptrdst[i] = (unsigned char)ptrsrc[i];
		if (ptrsrc[i] == (unsigned char)c)
			return (&ptrdst[i + 1]);
		++i;
	}
	return (NULL);
}
