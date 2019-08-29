/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 20:59:45 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			ft_remove_element(char **line, int i, int expand)
{
	ft_strremove_char(line, i);
	if ((*line)[i] && (*line)[i] == '\\')
		++i;
	else if (!(*line)[i])
		return (1);
	else if ((*line)[i] == '\n')
	{
		ft_strremove_char(line, i);
		--i;
	}
	else if (((*line)[i] == '"' || (*line)[i] == '\'')
			&& (expand == 0 || expand > 0))
	{
		ft_strremove_char(line, i);
		--i;
	}
	return (0);
}
