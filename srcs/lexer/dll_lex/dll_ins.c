/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_ins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:45:48 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 18:45:58 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	dllinsfront(t_lex **head, t_lex **node)
{
	(*node)->next = (*head);
	(*node)->prev = NULL;
	if (*head)
		(*head)->prev = (*node);
	(*head) = (*node);
}

void	dllinsback(t_lex **tail, t_lex **node)
{
	(*node)->next = NULL;
	(*node)->prev = (*tail);
	if (*tail)
		(*tail)->next = (*node);
	(*tail) = (*node);
}

void	dllinsafter(t_lex **prev_node, t_lex **node)
{
	(*node)->next = (*prev_node)->next;
	(*node)->prev = (*prev_node);
	(*prev_node)->next = (*node);
	if ((*node)->next)
		(*node)->next->prev = (*node);
}

void	dllinsbefore(t_lex **next_node, t_lex **node)
{
	(*node)->next = (*next_node);
	(*node)->prev = (*next_node)->prev;
	(*next_node)->prev = (*node);
	(*node)->prev->next = (*node);
}
