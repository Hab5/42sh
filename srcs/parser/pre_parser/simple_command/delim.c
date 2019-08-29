/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:47:41 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 20:47:43 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_delim(t_lex **head, t_lex **start, t_lex **end)
{
	*start = *head;
	*end = *head;
}

void	set_end(t_lex **end)
{
	while (*end && type_to_end_on((*end)->token->type))
		*end = (*end)->next;
}

void	set_start(t_lex **start)
{
	while (*start && type_to_ignore((*start)->token->type))
		*start = (*start)->next;
}

t_lex	*identify_delim(t_lex **start, t_lex **end)
{
	set_start(start);
	*end = *start;
	set_end(end);
	return (*start);
}
