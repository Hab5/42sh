/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:38:42 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/24 21:31:16 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	ptr[size] = '\0';
	return (ptr);
}
