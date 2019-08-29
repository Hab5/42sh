/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:01:47 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 09:59:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrayjoin(char **src, char *str)
{
	char	**dst;
	int		len;

	if (!(*src))
		return (NULL);
	len = ft_arraylen(src);
	if (!(dst = (char**)malloc(sizeof(char*) * (len + 2))))
		return (NULL);
	len = -1;
	while (src[++len])
		dst[len] = ft_strdup(src[len]);
	if (str)
		dst[len++] = ft_strdup(str);
	dst[len] = NULL;
	return (dst);
}
