/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:54:24 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 03:31:41 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*add_delim(t_lex **lex)
{
	t_lex	*head;
	t_lex	*tail;
	t_lex	*node;
	t_lex	*nd_node;
	t_token	*token;

	token = create_token("delim", DELIM);
	node = new_node(&token);
	nd_node = new_node(&token);
	head = *lex;
	tail = *lex;
	while (tail && tail->next)
		tail = tail->next;
	dllinsfront(&head, &nd_node);
	dllinsback(&tail, &node);
	clean_inside_token(&token);
	return (head);
}

void	add_token(t_lex **lexer, t_token **token)
{
	t_lex	*tail;
	t_lex	*node;

	node = new_node(token);
	tail = *lexer;
	if (!(*lexer))
		*lexer = node;
	else
	{
		while (tail->next)
			tail = tail->next;
		dllinsback(&tail, &node);
	}
}

t_token	*word_or_number(char *data)
{
	t_token	*token;

	token = NULL;
	if (ft_isnumbers(data))
		token = create_token(data, NUMBER);
	else
		token = create_token(data, WORD);
	return (token);
}

void	compare_types(t_tab_type **tab_of_type, t_token **token, char *word)
{
	int		i;

	i = 0;
	while ((*tab_of_type)[i].type != NUL)
	{
		if (!(ft_strcmp(word, (*tab_of_type)[i].str)))
			*token = create_token((*tab_of_type)[i].str, \
					(*tab_of_type)[i].type);
		i++;
	}
	if (!(*token))
		*token = word_or_number(word);
}

t_token	*check_type(t_tab_type **tab_of_type, char *input, int start, int end)
{
	char	*word;
	t_token	*token;

	token = NULL;
	word = ft_strsub(input, start, end - start);
	compare_types(tab_of_type, &token, word);
	ft_strdel(&word);
	return (token);
}
