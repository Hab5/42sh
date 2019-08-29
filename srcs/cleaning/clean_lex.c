/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:18:28 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/26 03:30:19 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	clean_inside_token(t_token **token)
{
	if (token && (*token))
	{
		clean_lex(&((*token)->command));
		ft_strdel(&((*token)->data));
		free(*token);
		(*token) = NULL;
	}
}

void	clean_lex(t_lex **lex)
{
	if ((!lex) || (!(*lex)))
		return ;
	if ((*lex)->next)
		clean_lex(&(*lex)->next);
	clean_redir(&((*lex)->redir));
	clean_inside_token(&(*lex)->token);
	free((*lex));
	(*lex) = NULL;
}
