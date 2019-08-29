/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:56:42 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/15 16:01:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*add_dquote_to_str(char *str)
{
	char	*des;
	int		i;
	int		j;
	int		len;

	i = 1;
	j = 0;
	len = ft_strlen(str) + 2;
	if (!(des = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	des[0] = '"';
	while (str[j])
		des[i++] = str[j++];
	des[i++] = '"';
	des[i] = 0;
	return (des);
}

char	*add_squote_to_str(char **str_addr)
{
	char	*str;
	char	*des;
	int		i;
	int		j;
	int		len;

	str = *str_addr;
	i = 1;
	j = 0;
	len = ft_strlen(str) + 3;
	if (!(des = (char *)ft_memalloc(sizeof(char) * len)))
		return (NULL);
	des[0] = '\'';
	while (str[j])
		des[i++] = str[j++];
	des[i++] = '\'';
	des[i] = '\0';
	return (des);
}
