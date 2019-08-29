/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:33:01 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 07:54:57 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"

static char	g_depth[2056];
static int	g_di;

void		print_push(char c)
{
	g_depth[g_di++] = ' ';
	g_depth[g_di++] = c;
	g_depth[g_di++] = ' ';
	g_depth[g_di++] = ' ';
	g_depth[g_di] = 0;
}

void		pretty_print(t_ast *tree)
{
	ft_putchar('[');
	ft_putstr(tree->token->data);
	ft_putstr("]\n");
	if (tree->l)
	{
		ft_putstr(g_depth);
		ft_putstr(" ├──");
		print_push('|');
		if (tree->r)
			pretty_print(tree->r);
		else
			ft_putstr("[null]\n");
		g_depth[g_di -= 4] = 0;
		ft_putstr(g_depth);
		ft_putstr(" └──");
		print_push(' ');
		pretty_print(tree->l);
		g_depth[g_di -= 4] = 0;
	}
}

t_ast		*node_ast(t_token *token, t_ast *l, t_ast *r)
{
	t_ast	*node;

	if (!(node = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	node->token = token;
	node->l = l;
	node->r = r;
	return (node);
}

void		clean_ast(t_ast *node)
{
	if (!node)
		return ;
	clean_ast(node->l);
	clean_ast(node->r);
	free(node);
	node = NULL;
}

t_ast		*ast_parser(t_lex *tokens)
{
	t_ast	*ast;

	g_out = 0;
	g_stream = tokens;
	ast = expr(0);
	if (g_out == 1)
	{
		clean_ast(ast);
		return (NULL);
	}
	if (g_print_ast == 1)
	{
		ft_putstr("---------------AST---------------\n");
		pretty_print(ast);
		ft_putstr("---------------------------------\n");
	}
	return (ast);
}
