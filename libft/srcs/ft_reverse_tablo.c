/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_tablo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:08:58 by sbelondr          #+#    #+#             */
/*   Updated: 2019/04/08 11:06:27 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse_tablo(char (*lst)[BUF_S])
{
	char	tmp[BUF_S];
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(*lst) - 1;
	ft_bzero(&tmp, BUF_S);
	while (++i <= len)
		tmp[i] = (*lst)[len - i];
	ft_bzero(&(*lst), BUF_S);
	i = -1;
	while (tmp[++i])
		(*lst)[i] = tmp[i];
}
