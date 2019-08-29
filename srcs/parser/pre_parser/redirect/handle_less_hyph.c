/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_less_hyph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:53:20 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/09 07:33:19 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_redir	*redir_struct_less_hyph(t_lex **start)
{
	t_redir	*redir_info;
	t_lex	*ptr;

	ptr = *start;
	if (!(redir_info = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	if (!(redir_info->src_fd = (char **)ft_memalloc(sizeof(char *) * 3)))
		return (NULL);
	redir_info->type = LESSAMPHYPH;
	if (ptr->token->type == NUMBER)
		redir_info->src_fd[0] = ft_strdup(ptr->token->data);
	else
		ft_default(&redir_info);
	redir_info->close = 1;
	return (redir_info);
}

int		handle_less_hyph(t_lex **command_node)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*before_start;
	t_redir	*redir_info;

	start = *command_node;
	end = NULL;
	redir_info = NULL;
	while (start && start->token->type != LESSAMPHYPH)
		start = start->next;
	if (start)
	{
		start_grammar_great(&start);
		end = start;
		if (end->token->type == NUMBER)
			end = end->next;
		before_start = detaching(&start, &end);
		redir_info = redir_struct_less_hyph(&start);
		clean_lex(&start);
		attach_redir_node(&redir_info, &before_start);
	}
	return (0);
}
