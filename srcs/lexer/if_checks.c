/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:52:34 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 20:53:46 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		ft_isnumbers(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int		is_in_tab(t_tab_type **tab_of_type, char c)
{
	int		i;

	i = 0;
	while ((*tab_of_type)[i].type != NUL)
	{
		if ((*tab_of_type)[i].str[0] == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_amper(char c)
{
	if (c == '&')
		return (1);
	return (0);
}

int		is_lesser_greater(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int		is_hyph(char c)
{
	if (c == '-')
		return (1);
	return (0);
}
