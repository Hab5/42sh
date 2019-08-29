/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:30:18 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/01 11:55:31 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "sh21.h"
#include "parser.h"

t_token			*next(void)
{
	g_stream = (g_stream->next) ? g_stream->next : g_stream;
	return (g_stream) ? (g_stream->token) : (NULL);
}

t_token			*peek(void)
{
	return (g_stream->next) ? (g_stream->next->token) : (NULL);
}

int				bp(t_token *token)
{
	if (token == NULL)
		return (0);
	else if (token->type == DELIM)
		return (-10);
	else if (token->type == CMD)
		return (10);
	else if (token->type == SCOLON)
		return (20);
	else if (token->type == AMP)
		return (25);
	else if (token->type == DAMP)
		return (25);
	else if (token->type == DPIPE)
		return (25);
	else if (token->type == SPIPE)
		return (30);
	else
		return (0);
}
