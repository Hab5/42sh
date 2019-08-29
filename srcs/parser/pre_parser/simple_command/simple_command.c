/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:47:22 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 03:30:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	simple_command(t_lex **head)
{
	t_lex	*start;
	t_lex	*end;
	t_token	*token;
	t_lex	*node;

	set_delim(head, &start, &end);
	while (identify_delim(&start, &end))
	{
		detach(&start, &end);
		token = create_command_token(&start, CMD);
		node = new_node(&token);
		attach(head, &node, &end);
		ft_strdel(&token->data);
		ft_memdel((void **)&token);
		set_delim(head, &start, &end);
	}
}
