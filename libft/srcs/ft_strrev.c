/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:20:49 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 14:25:05 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		strlen;
	char	temp;

	strlen = 0;
	i = 0;
	while (str[strlen])
		strlen++;
	strlen--;
	while (i < strlen)
	{
		temp = str[strlen];
		str[strlen] = str[i];
		str[i] = temp;
		i++;
		strlen--;
	}
	return (str);
}
