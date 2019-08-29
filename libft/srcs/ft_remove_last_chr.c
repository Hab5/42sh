/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_last_chr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:45:17 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 15:47:27 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_remove_last_chr(char **str)
{
	int		i;
	int		len;
	int		index;
	char	*tmp;

	i = -1;
	len = ft_strlen(*str);
	while ((*str)[++i] && i < (len - 1))
		if ((*str)[i] == '\n')
			index = i;
	tmp = ft_strsub((*str), 1, index);
	ft_strdel(&(*str));
	(*str) = tmp;
}
