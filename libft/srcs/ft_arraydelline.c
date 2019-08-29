/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydelline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:37:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/15 15:28:33 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraydelline(char ***src, int line)
{
	int		i;
	int		k;
	int		len;
	char	**dst;

	if ((!src) || (!(*src)) || ft_arraylen(*src) < line)
		return ;
	len = ft_arraylen(*src);
	if (!(dst = (char**)malloc(sizeof(char*) * len)))
		return ;
	i = -1;
	k = -1;
	while (++i < len)
		if (i != line)
			dst[++k] = ft_strdup((*src)[i]);
	dst[++k] = NULL;
	ft_arraydel(&(*src));
	*src = dst;
}
