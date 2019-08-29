/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:09:34 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 18:46:19 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*create_token(char *str, t_type types)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup(str);
	token->command = NULL;
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = types;
	return (token);
}

t_token		*create_command_token(t_lex **command, t_type types)
{
	t_token	*token;

	token = NULL;
	if (!(token = (t_token *)ft_memalloc(sizeof(token))))
		return (NULL);
	token->data = ft_strdup("Command");
	token->command = *command;
	if (!token->data)
	{
		free(token);
		return (NULL);
	}
	token->type = types;
	return (token);
}
