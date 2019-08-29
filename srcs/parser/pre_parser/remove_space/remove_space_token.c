/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:18:54 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 08:12:25 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_only_space(t_lex **node_cmd)
{
	t_lex	*ptr;

	ptr = (*node_cmd)->token->command;
	if (ptr->next == NULL && ptr->token->type == SPACE)
		return (1);
	if (ptr->token->type == DELIM && ptr->next->token->type == SPACE \
			&& ptr->next->next == NULL)
		return (1);
	return (0);
}

void	remove_node(t_lex **node_cmd_space)
{
	t_lex	*prev;
	t_lex	*next;
	t_lex	*ptr;

	ptr = *node_cmd_space;
	prev = ptr->prev;
	next = ptr->next;
	prev->next = next;
	if (next)
		next->prev = prev;
	if (ptr->token->data[0])
		ft_strdel(&ptr->token->data);
	ptr->token->type = 0;
	clean_lex(&ptr->token->command);
	ft_memdel((void **)&ptr->token);
	dll_del_node(&ptr);
}

void	remove_space_token(t_lex **lexer)
{
	t_lex	*ptr;
	t_lex	*tmp;

	ptr = *lexer;
	while (ptr)
	{
		if (ptr->token->type == CMD)
		{
			if (is_only_space(&ptr))
			{
				tmp = ptr;
				ptr = ptr->next;
				remove_node(&tmp);
			}
			else
				ptr = ptr->next;
		}
		else
			ptr = ptr->next;
	}
}
