/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:12:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:33:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	is_special_variable(char *str)
{
	if ((!str) || ft_strlen(str) != 1)
		return (0);
	if (str[0] == '?' || str[0] == '0' || str[0] == '-' || str[0] == '#')
		return (1);
	return (0);
}

int			check_format_variable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (is_special_variable(str));
	return (1);
}
