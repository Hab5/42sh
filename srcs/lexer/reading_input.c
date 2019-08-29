/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:21:29 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 20:32:51 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	reading_input(char *input, t_lex **lex)
{
	t_token		*tok;
	t_tab_type	*tab_of_type;

	reading_loop(input, lex, &tok, &tab_of_type);
	ft_memdel((void **)&tab_of_type);
}
