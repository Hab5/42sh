/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 10:58:33 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/07 18:13:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_split(char *str)
{
	if (*str == ';')
		return (1);
	if (*str == '&' && ((!*(str + 1)) || *(str + 1) != '&') && ((!*(str - 1))
				|| *(str - 1) != '&'))
		return (1);
	return (0);
}

static int	cnt_words(char *s)
{
	int	cnt;
	int	nb_char;
	int	nb_words;

	cnt = 0;
	nb_words = 0;
	while (s[cnt])
	{
		while (s[cnt] && is_split(s + cnt))
			cnt++;
		nb_char = 0;
		while (s[cnt + nb_char] && is_split(s + cnt + nb_char) == 0)
			nb_char++;
		nb_words += (nb_char > 0) ? 1 : 0;
		cnt += nb_char;
		while (s[cnt] && is_split(s + cnt))
			cnt++;
	}
	return (nb_words);
}

static void	ft_split(char *s, char ***result)
{
	int	i;
	int	nb_words;
	int	nb_char;

	i = 0;
	nb_words = -1;
	while (s[i])
	{
		while (s[i] && is_split(s + i))
			i++;
		nb_char = 0;
		while (s[i + nb_char] && is_split(s + i + nb_char) == 0)
			nb_char++;
		(nb_char > 0) ? (*result)[++nb_words] = ft_strsub(s, i, nb_char) : 0;
		i += nb_char;
		while (s[i] && is_split(s + i))
			i++;
	}
	(*result)[++nb_words] = 0;
}

char		**ft_strsplit_commands(char *s)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = cnt_words(s);
	if (words == 0)
		return (NULL);
	if (!(result = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	ft_split((char*)s, &result);
	return (result);
}
