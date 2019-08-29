/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:44:50 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/08 18:35:25 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_error(int code_error)
{
	if (code_error == 0)
		ft_putendl("42sh: syntax error near unexpected token `r_token'");
}

int		handle_tok(t_token **tok, t_lex **lex)
{
	if ((*tok)->data[0])
		add_token(lex, tok);
	ft_strdel(&(*tok)->data);
	ft_memdel((void **)tok);
	return (0);
}

int		handle_classic_case(int *i, int *last_t, char **input)
{
	if ((*i) == (*last_t))
	{
		if (dub_possible((*input)[*i]))
			check_double(*input, i);
		(*i)++;
	}
	return (1);
}

void	handle_word_case(int *i, char **input, int *last_t, int *to_check)
{
	(*i)++;
	if ((*input)[(*i)] == '\0')
	{
		if ((*i) != (*last_t))
			(*to_check) = 1;
	}
}

int		handle_string_case(int *i, int *last_t, char **input, t_token **tok)
{
	if ((*i) == (*last_t))
	{
		if ((*input)[(*i)] == '\"')
			(*tok) = handle_string((*input), i, last_t, '\"');
		else
			(*tok) = handle_string_squote((*input), i, last_t, '\'');
	}
	return (1);
}
