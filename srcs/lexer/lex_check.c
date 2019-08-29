/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 08:04:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 10:02:39 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		init_variables(t_token **tok, int *to_check, int *i, t_tab_type **t)
{
	*tok = NULL;
	*to_check = 0;
	*i = 0;
	set_tab_types(t);
	return (0);
}

int		dub_possible(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

int		ft_isreallyspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
			|| c == '\f' || c == '\r')
		return (1);
	return (0);
}
