/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:46:40 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 08:12:37 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Made a separate function to be able to use it for start and end
*/

int		is_operator(t_type type)
{
	if (type == SPIPE || type == DPIPE || type == AMP \
			|| type == DAMP || type == SCOLON)
		return (1);
	return (0);
}

/*
** We want to end on the node of one of those type
*/

int		type_to_end_on(t_type type)
{
	if (is_operator(type) || type == DELIM)
		return (0);
	return (1);
}

/*
** We want to start on the node after those type
*/

int		type_to_ignore(t_type type)
{
	if (is_operator(type) || type == DELIM || type == CMD)
		return (1);
	return (0);
}
