/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:56:21 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 03:19:13 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*handle_string(char *input, int *i, int *last_t, char c)
{
	char	*word;
	char	*work_dquote;
	t_token	*tok;

	word = NULL;
	tok = NULL;
	(*last_t) = ++(*i);
	while (input[*i] && input[(*i)] != c)
		(*i)++;
	word = ft_strsub(input, *last_t, *i - *last_t);
	work_dquote = add_dquote_to_str(word);
	ft_strdel(&word);
	tok = create_token(work_dquote, WORD);
	ft_strdel(&work_dquote);
	if (input[*i])
		(*i)++;
	return (tok);
}

t_token	*handle_string_squote(char *input, int *i, int *last_t, char c)
{
	char	*word;
	char	*word_squote;
	t_token	*tok;

	word = NULL;
	word_squote = NULL;
	tok = NULL;
	(*last_t) = ++(*i);
	while (input[*i] && input[(*i)] != c)
		(*i)++;
	word = ft_strsub(input, *last_t, *i - *last_t);
	word_squote = add_squote_to_str(&word);
	ft_memdel((void **)&word);
	tok = create_token(word_squote, WORD);
	ft_memdel((void **)&word_squote);
	if (input[*i])
		(*i)++;
	return (tok);
}

void	check_double(char *input, int *i)
{
	if (input[(*i) + 1])
	{
		if (input[(*i)] == input[(*i) + 1])
			(*i)++;
		else if (is_amper(input[(*i)]))
		{
			if (is_greater(input[(*i) + 1]))
				(*i)++;
		}
		else if (is_lesser_greater(input[(*i)]))
		{
			if (is_amper(input[(*i) + 1]))
			{
				if ((input[(*i) + 2]) && (is_hyph(input[(*i) + 2])))
					(*i)++;
				(*i)++;
			}
		}
	}
}

int		handle_whitespace(char *input, int i, t_lex **lex)
{
	int		cpy;
	t_token	*tok;

	tok = NULL;
	cpy = i;
	while (input[i] && ft_isreallyspace(input[i]))
		i++;
	if (i != cpy)
	{
		tok = create_token(" ", SPACE);
		add_token(lex, &tok);
		clean_inside_token(&tok);
	}
	return (i);
}
