/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_limits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 05:29:33 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 20:52:24 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*identify_start(t_lex **head)
{
	t_lex	*ptr;
	t_lex	*start;

	ptr = (*head);
	start = NULL;
	while (ptr->next != NULL && ptr->next->token->type != DELIM)
	{
		if (ptr->token->type == WORD)
		{
			start = ptr;
			return (start);
		}
		ptr = ptr->next;
	}
	return (start);
}

t_lex	*identify_end(t_lex **start)
{
	t_lex	*end;

	end = (*start);
	while (end->next->token->type == WORD)
		end = end->next;
	return (end);
}
