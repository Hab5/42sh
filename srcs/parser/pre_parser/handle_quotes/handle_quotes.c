/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 04:25:35 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/25 07:00:24 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*create_the_node(char **str)
{
	t_token	*tok;
	t_lex	*node;

	tok = create_token((*str), WORD);
	node = new_node(&tok);
	ft_strdel(&(tok->data));
	ft_memdel((void**)&tok);
	return (node);
}

char	*create_merged_string(t_lex **head)
{
	t_lex	*ptr;
	char	*str;
	char	*cache;

	cache = NULL;
	ptr = (*head);
	str = ft_strdup(ptr->token->data);
	ptr = ptr->next;
	while (ptr)
	{
		cache = ft_strjoin(str, ptr->token->data);
		ft_strdel(&str);
		str = cache;
		ptr = ptr->next;
	}
	return (str);
}

void	merge_string_token(t_lex **start, t_lex **end)
{
	t_lex	*before_start;
	t_lex	*after_end;
	t_lex	*node;
	char	*merged_string;

	after_end = (*end)->next;
	before_start = detaching(start, end);
	merged_string = create_merged_string(start);
	node = create_the_node(&merged_string);
	dllinsafter(&before_start, &node);
	ft_strdel(&merged_string);
	clean_lex(start);
}

void	handle_quotes(t_lex **head)
{
	t_lex	*start;
	t_lex	*end;
	t_lex	*ptr;

	start = NULL;
	end = NULL;
	if ((*head)->token->type == 21 && (!(*head)->next))
		return ;
	ptr = *head;
	if ((start = identify_start(head)))
	{
		end = identify_end(&start);
		if (end != start)
			merge_string_token(&start, &end);
		handle_quotes(&((*head)->next));
	}
}
