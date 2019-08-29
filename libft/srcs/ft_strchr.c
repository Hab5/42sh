/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:46:42 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 13:44:26 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c != '\0')
	{
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
				return ((char *)s + i);
			i++;
		}
	}
	else
	{
		while (s[i])
			i++;
		return ((char *)s + i);
	}
	return (NULL);
}
