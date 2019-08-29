/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jointhree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:17:35 by apruvost          #+#    #+#             */
/*   Updated: 2019/05/08 02:20:22 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_jointhree(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*bin;

	if ((str = ft_strjoin(s1, s2)) == NULL)
		return (NULL);
	bin = str;
	if ((str = ft_strjoin(str, s3)) == NULL)
	{
		ft_strdel(&bin);
		return (NULL);
	}
	ft_strdel(&bin);
	return (str);
}
