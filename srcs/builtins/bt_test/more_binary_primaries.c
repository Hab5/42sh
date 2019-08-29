/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_binary_primaries.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 07:48:03 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 15:09:11 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check_hyph(char *str1, int *i)
{
	if (str1[0] == '-' || str1[0] == '+')
		(*i) = 1;
}

int		verify_only_alpha(char *str1, char *str2)
{
	int		i;

	i = 0;
	check_hyph(str1, &i);
	while (str1[i])
	{
		if (ft_isdigit(str1[i]))
			i++;
		else
			return (1);
	}
	i = 0;
	check_hyph(str2, &i);
	while (str2[i])
	{
		if (ft_isdigit(str2[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int		equal_test(char *str1, char *str2, char *str3)
{
	if (ft_strcmp(str1, str3) == 0)
		return (0);
	(void)str2;
	return (1);
}

int		notequal_test(char *str1, char *str2, char *str3)
{
	if (ft_strcmp(str1, str3) == 0)
		return (1);
	(void)str2;
	return (0);
}
