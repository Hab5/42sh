/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:46:32 by skuppers          #+#    #+#             */
/*   Updated: 2018/02/10 10:44:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnchr(char *line, char c)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
		if (line[i] == c)
			return (i);
		else
			i++;
	return (ft_strlen(line));
}
