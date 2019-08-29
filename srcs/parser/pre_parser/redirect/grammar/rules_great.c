/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 07:34:20 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/09 07:34:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_grammar_great(t_lex **start)
{
	if ((*start)->prev && (*start)->prev->token->type == NUMBER)
		(*start) = (*start)->prev;
}

int		end_grammar_great(t_lex **start, t_lex **end, t_type type_check)
{
	(*end) = (*start);
	if ((*end)->next)
		(*end) = (*end)->next;
	else
		return (1);
	if ((*end) && (*end)->token->type == type_check && (*end)->next)
		(*end) = (*end)->next;
	if ((*end) && (*end)->token->type == type_check && !((*end)->next))
		return (1);
	if (((*end)->token->type == SPACE) && ((*end)->next))
		(*end) = (*end)->next;
	if ((*end)->token->type == SPACE && !((*end)->next))
		return (1);
	if ((*end)->token->type != NUMBER && (*end)->token->type != WORD)
		return (1);
	return (0);
}
