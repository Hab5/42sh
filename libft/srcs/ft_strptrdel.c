/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strptrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:42:19 by apruvost          #+#    #+#             */
/*   Updated: 2019/03/06 14:12:08 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strptrdel(char ***as)
{
	int	i;

	i = 0;
	if (as && *as)
	{
		while ((*as)[i])
		{
			ft_strdel(&((*as)[i]));
			i++;
		}
		free(*as);
		*as = 0;
	}
}