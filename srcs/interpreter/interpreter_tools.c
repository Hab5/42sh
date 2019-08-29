/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 05:08:50 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 07:52:07 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "job.h"

int		solo_tree(t_ast *node, t_pos *pos)
{
	if (node->token->type == CMD)
	{
		run_cmd(node->token, pos, 0);
		return (1);
	}
	if (node->token->type == AMP && node->l->token->type == CMD && !node->r)
	{
		manage_id_job(1);
		run_cmd(node->l->token, pos, 1);
		return (1);
	}
	else
		return (-1);
}

void	dpipe_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == DPIPE)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			run_cmd(node->l->token, pos, bg);
			if (check_last() != 0)
				run_cmd(node->r->token, pos, bg);
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			run_cmd(node->l->token, pos, bg);
	}
}

void	damp_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == DAMP)
	{
		if (node->l->token->type == CMD && node->r->token->type == CMD)
		{
			run_cmd(node->l->token, pos, bg);
			if (check_last() == 0)
				run_cmd(node->r->token, pos, bg);
		}
		if (node->l->token->type == CMD && node->r->token->type != CMD)
			run_cmd(node->l->token, pos, bg);
	}
}

void	edge_case(t_ast *node, t_pos *pos, int bg)
{
	if (node->token->type == SCOLON || node->token->type == AMP)
		if (node->l->token->type != CMD && node->r\
							&& node->r->token->type == CMD)
			run_cmd(node->r->token, pos, bg);
	if (node->token->type == DPIPE)
		if (node->l->token->type != CMD && node->r->token->type == CMD)
			if (check_last() != 0)
				run_cmd(node->r->token, pos, bg);
	if (node->token->type == DAMP)
		if (node->l->token->type != CMD && node->r->token->type == CMD)
			if (check_last() == 0)
				run_cmd(node->r->token, pos, bg);
}
