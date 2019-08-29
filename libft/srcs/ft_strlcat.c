/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:04:58 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 13:56:59 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (dst[i] && i < size)
		i++;
	dstlen = i;
	while (src[count] && dstlen + 1 < size)
	{
		dst[dstlen] = src[count];
		dstlen++;
		count++;
	}
	if (dstlen < size)
		dst[dstlen] = '\0';
	return (i + ft_strlen(src));
}
