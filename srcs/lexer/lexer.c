/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 20:32:51 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		handle_backslash(int *i, char *input)
{
	(*i)++;
	if (input[(*i)])
		(*i)++;
	return (1);
}

int		lexer_begin_loop(char *input, int *i, int last_t)
{
	int		to_check;

	to_check = 0;
	if (ft_isreallyspace(input[*i]) && (*i != last_t))
		to_check = 1;
	else if (input[*i] == '\\' && (*i != last_t))
		to_check = 1;
	else if (input[*i] == '\\')
		to_check = handle_backslash(i, input);
	return (to_check);
}

void	reading_loop(char *input, t_lex **lex, t_token **tok, t_tab_type **t)
{
	int		i;
	int		last_t;
	int		to_check;

	last_t = init_variables(tok, &to_check, &i, t);
	while (input[i])
	{
		i = handle_whitespace(input, i, lex);
		last_t = i;
		while (input[i] && !(to_check))
		{
			if ((to_check = lexer_begin_loop(input, &i, last_t)))
				;
			else if (input[i] == '\"' || input[i] == '\'')
				to_check = handle_string_case(&i, &last_t, &input, tok);
			else if (is_in_tab(t, input[i]))
				to_check = handle_classic_case(&i, &last_t, &input);
			else
				handle_word_case(&i, &input, &last_t, &to_check);
		}
		if (to_check && !(*tok))
			(*tok) = check_type(t, input, last_t, i);
		if (to_check)
			to_check = handle_tok(tok, lex);
	}
}

void	prepare_input(char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while ((tmp = ft_strchr(input, '\\')) != NULL && *(tmp + 1) == '\n')
	{
		i = tmp + 2 - input;
		j = tmp - input;
		while (input[i] != '\0')
			input[j++] = input[i++];
		input[j] = '\0';
	}
}

t_lex	*lexer(char *input)
{
	t_lex	*lex;

	lex = NULL;
	prepare_input(input);
	reading_input(input, &lex);
	lex = add_delim(&lex);
	handle_quotes(&lex);
	simple_command(&lex);
	if (handle_redir(&lex))
	{
		clean_lex(&lex);
		ft_error(0);
		return (NULL);
	}
	remove_space_token(&lex);
	return (lex);
}
