/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:34:29 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 22:05:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "sh21.h"
# include "lexer.h"

int					g_print_ast;
t_lex				*g_stream;
int					g_out;

# define OP (t->type == SCOLON || t->type == SPIPE || t->type == AMP)
# define MORE_OP (t->type == DAMP || t->type == DPIPE || t->type == DELIM)

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*l;
	struct s_ast	*r;
}					t_ast;

void				pretty_print(t_ast *tree);
t_ast				*node_ast(t_token *token, t_ast *l, t_ast *r);
t_token				*next(void);
t_token				*peek(void);
int					bp(t_token *token);
void				clean_ast(t_ast *node);

t_ast				*expr(int rbp);
t_ast				*ast_parser(t_lex *tokens);

int					solo_tree(t_ast *node, t_pos *pos);
void				damp_case(t_ast *node, t_pos *pos, int bg);
void				dpipe_case(t_ast *node, t_pos *pos, int bg);
int					interpreter(t_ast *node, t_pos *pos, int bg);
void				edge_case(t_ast *node, t_pos *pos, int bg);
int					*run_cmd(t_token *cmd_list, t_pos *pos, int bg);
int					*run_pipe(t_token *cmd_list, t_pos *pos, int end_pipe,
						int bg);

int					check_last(void);
#endif
