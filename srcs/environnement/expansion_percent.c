/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:12:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/13 01:51:46 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** comme # mais inverse. ex: salut#sal > salut ;
** salut#ut > sal ; salut#salut > ; salut#salutoi > salut
*/

static int	assign_value_parameter_percents(int *index, char **stock,
		char *value, char *parameter)
{
	ft_strdel(stock);
	(*index) += value[(*index) + 1] && value[(*index) + 1] == '%' ? 2 : 1;
	(*stock) = value[(*index)] ? search_var(value + (*index)) : NULL;
	(*index) = ft_strlen(parameter);
	return (ft_strlen(*stock));
}

static char	*value_parameter_percents(int index, char **stock, char *value)
{
	char	*parameter;
	char	*dst;
	int		i;

	parameter = value_line_path(*stock, 0);
	if (!parameter)
		return (NULL);
	i = assign_value_parameter_percents(&index, stock, value, parameter);
	if (i <= index)
		while (--index > -1 && --i > -1 && parameter[index] && (*stock)[i])
			if (parameter[index] != (*stock)[i])
			{
				i = 0;
				break ;
			}
	dst = ft_strsub(parameter, 0, index + 1);
	ft_strdel(&parameter);
	return (dst);
}

char		*parameter_percents(char *value)
{
	char	*dst;
	char	*stock;
	int		index;

	index = ft_chr_index(value, '%');
	stock = ft_strsub(value, 0, index);
	if (check_format_variable(stock) == 0)
	{
		ft_strdel(&stock);
		display_error_expansion(value);
		return (NULL);
	}
	dst = value_parameter_percents(index, &stock, value);
	ft_strdel(&stock);
	return (dst);
}
