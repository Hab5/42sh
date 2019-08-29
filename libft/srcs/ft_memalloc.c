/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:19:00 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/22 17:10:20 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (!(ptr = malloc(sizeof(ptr) * size)))
		return (NULL);
	while (i < size)
	{
		ptr[i] = 0;
		++i;
	}
	ptr[i] = 0;
	return (ptr);
}
