/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_once.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 04:49:38 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 15:52:06 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_second(char *str, char **tab, int count)
{
	int		total;
	int		start;

	start = count;
	total = 0;
	while (str[count])
	{
		count++;
		total++;
	}
	if (count == start)
		return (1);
	if (!(tab[1] = ft_memalloc(sizeof(char) * (total + 1))))
		return (1);
	total = 0;
	while (str[start])
	{
		tab[1][total] = str[start];
		start++;
		total++;
	}
	tab[1][total] = '\0';
	return (0);
}

static int	malloc_first(char *str, char c, char **tab)
{
	int		count;

	count = 0;
	while (str[count])
	{
		if (str[count] == c)
		{
			if (!(tab[0] = (char*)ft_memalloc(sizeof(char) * (count + 1))))
				return (-1);
			ft_strncpy(tab[0], str, count);
			tab[0][count] = '\0';
			count++;
			break ;
		}
		count++;
	}
	return (count);
}

static int	exist(char *str, char c)
{
	if (!(ft_strchr(str, c)))
		return (1);
	return (0);
}

char		**split_once(char *str, char c)
{
	int		count;
	char	**tab;

	count = 0;
	if (exist(str, c))
		return (NULL);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * 3)))
		return (NULL);
	count = malloc_first(str, c, tab);
	if (count <= 1)
	{
		free(tab[0]);
		free(tab);
		return (NULL);
	}
	if (malloc_second(str, tab, count))
	{
		free(tab[0]);
		free(tab);
		return (NULL);
	}
	tab[2] = NULL;
	return (tab);
}
