/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 10:58:33 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/08 13:45:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_split(char c, char spl)
{
	if (!spl)
		return (ft_isspace(c));
	else
		return ((c == spl) ? 1 : 0);
}

static int	cnt_words(const char *s, char c)
{
	int	cnt;
	int	nb_char;
	int	nb_words;

	cnt = 0;
	nb_words = 0;
	while (s[cnt])
	{
		while (s[cnt] && is_split(s[cnt], c))
			cnt++;
		nb_char = 0;
		while (s[cnt + nb_char] && is_split(s[cnt + nb_char], c) == 0)
			nb_char++;
		nb_words += (nb_char > 0) ? 1 : 0;
		cnt += nb_char;
		while (s[cnt] && is_split(s[cnt], c))
			cnt++;
	}
	return (nb_words);
}

static void	ft_split(const char *s, char c, char ***result)
{
	int	i;
	int	nb_words;
	int	nb_char;

	i = 0;
	nb_words = -1;
	while (s[i])
	{
		while (s[i] && is_split(s[i], c))
			i++;
		nb_char = 0;
		while (s[i + nb_char] && is_split(s[i + nb_char], c) == 0)
			nb_char++;
		(nb_char > 0) ? (*result)[++nb_words] = ft_strsub(s, i, nb_char) : 0;
		i += nb_char;
		while (s[i] && is_split(s[i], c))
			i++;
	}
	(*result)[++nb_words] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	if (!c)
		c = 0;
	words = cnt_words(s, c);
	if (words == 0)
		return (NULL);
	if (!(result = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	ft_split(s, c, &result);
	return (result);
}
