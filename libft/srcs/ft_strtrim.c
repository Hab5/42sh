/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:26:09 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 14:06:34 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*ptr;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
		len--;
	j = -1;
	while (s[++j] == ' ' || s[j] == '\t' || s[j] == '\n')
		len--;
	if (len <= 0)
		len = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	s = s + j;
	j = 0;
	while (j < len)
		ptr[j++] = *s++;
	ptr[j] = '\0';
	return (ptr);
}
