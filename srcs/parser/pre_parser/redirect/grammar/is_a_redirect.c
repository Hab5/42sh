/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:37:02 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 03:05:04 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_a_redirect(t_type t)
{
	if (t == GREAT || t == GREATAMP || t == AMPGREAT || t == DGREAT
		|| t == LESS || t == LESSAMP || t == DLESS
		|| t == LESSAMPHYPH || t == GREATAMPHYPH)
		return (1);
	return (0);
}
