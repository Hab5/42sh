/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 22:17:10 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 01:59:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_arraydel(char ***line)
{
	int	i;

	i = -1;
	if (line && *line)
	{
		while ((*line)[++i])
			ft_strdel(&((*line)[i]));
		free(*line);
		*line = NULL;
	}
}
