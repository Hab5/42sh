/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 12:22:33 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 15:52:31 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_alloc_len(char const *str, char **tab)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i])
	{
		i++;
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0')
		{
			if (!(tab[j] = (char*)malloc(sizeof(char) * (len + 2))))
				return (NULL);
			j++;
			len = 0;
		}
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		len++;
	}
	return (tab);
}

static char	**ft_fill_memories(char const *str, char **tab)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		tab[j][len] = str[i];
		i++;
		len++;
		if (str[i] == '\0' || str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			tab[j][len] = '\0';
			j++;
			len = 0;
		}
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
	}
	return (tab);
}

static char	**ft_alloc_words(char const *str, char **tab)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		{
			words++;
			while (str[i] && !(str[i] == ' '
						|| str[i] == '\t' || str[i] == '\n'))
				i++;
		}
		else
			i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	tab[words] = 0;
	return (tab);
}

char		**ft_split_whitespaces(char const *str)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = 0;
	if (!(tab = ft_alloc_words(str, tab)))
		return (NULL);
	if (!(tab = ft_alloc_len(str, tab)))
		return (NULL);
	if (!(tab = ft_fill_memories(str, tab)))
		return (NULL);
	return (tab);
}
