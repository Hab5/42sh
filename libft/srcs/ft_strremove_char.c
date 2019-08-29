/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 11:00:42 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 11:01:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strremove_char(char **src, int i)
{
	char	*tmp;
	char	*tmp_bis;

	if (i == 0)
	{
		tmp = ft_strsub(*src, 1, ft_strlen(*src) - 1);
		ft_strdel(src);
		(*src) = tmp;
		return ;
	}
	tmp = ft_strsub(*src, 0, i);
	tmp_bis = ((*src)[i + 1]) ? ft_strsub(*src, i + 1, ft_strlen(*src) - i)
		: ft_strdup("");
	ft_strdel(src);
	(*src) = ft_strjoin(tmp, tmp_bis);
	ft_strdel(&tmp);
	ft_strdel(&tmp_bis);
}
