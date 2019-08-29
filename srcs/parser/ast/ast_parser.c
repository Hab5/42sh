/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:30:45 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 07:46:10 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "parser.h"

t_ast			*nud(t_token *t)
{
	if (t->type == CMD)
		return (node_ast(t, NULL, NULL));
	else if (OP && MORE_OP)
	{
		ft_putstr("42sh: parse error near: ");
		ft_putendl(t->data);
		g_out = 1;
		return (node_ast(t, NULL, NULL));
	}
	else
		return (NULL);
}

t_ast			*led(t_ast *left, t_token *t)
{
	if (t->type == AMP && peek()->type == DELIM)
		return (node_ast(t, left, NULL));
	else if (t->type == SCOLON)
		return (node_ast(t, left, expr(20)));
	else if (t->type == AMP || t->type == DAMP || t->type == DPIPE)
		return (node_ast(t, left, expr(25)));
	else if (t->type == SPIPE)
		return (node_ast(t, left, expr(30 - 1)));
	else if (t->type == CMD || t->type == DELIM)
	{
		ft_putstr("42sh: parse error near: ");
		ft_putendl(t->data);
		g_out = 1;
		return (left);
	}
	else
		return (NULL);
}

t_ast			*expr(int rbp)
{
	t_ast		*left;

	left = NULL;
	if (g_out == 1)
		return (left);
	left = nud(next());
	while (rbp < bp(peek()))
		left = led(left, next());
	return (left);
}
