/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:10:40 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 07:44:04 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "job.h"

void			background_case(t_ast *node, t_pos *pos, int *bg)
{
	if (node->token->type == AMP)
	{
		*bg = *bg + 1;
		if (node->l->token->type == CMD && node->r \
							&& node->r->token->type == CMD)
		{
			run_cmd(node->l->token, pos, *bg);
			run_cmd(node->r->token, pos, *bg - 1);
		}
		if (node->l->token->type == CMD && node->r \
							&& node->r->token->type != CMD)
			run_cmd(node->l->token, pos, *bg - 1);
	}
}

void			scolon_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == SCOLON)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			run_cmd(node->l->token, pos, bg);
			run_cmd(node->r->token, pos, bg);
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			run_cmd(node->l->token, pos, bg);
	}
}

void			spipe_case(t_ast *node, t_pos *pos, int bg)
{
	static int state;

	if (node->token->type == SPIPE)
	{
		if (state == 0)
			run_pipe(node->l->token, pos, state++, bg);
		else
			run_pipe(node->l->token, pos, 1, bg);
		if (node->r->token->type == CMD)
		{
			run_pipe(node->r->token, pos, 2, bg);
			state = 0;
		}
	}
}

int				interpreter(t_ast *node, t_pos *pos, int background)
{
	static int	bg;

	(void)background;
	if (!node)
		return (-1);
	background_case(node, pos, &bg);
	scolon_case(node, pos, bg);
	dpipe_case(node, pos, bg);
	damp_case(node, pos, bg);
	spipe_case(node, pos, bg);
	interpreter(node->l, pos, bg);
	if (node->token->type == AMP)
		bg--;
	interpreter(node->r, pos, bg);
	edge_case(node, pos, bg);
	return (0);
}
