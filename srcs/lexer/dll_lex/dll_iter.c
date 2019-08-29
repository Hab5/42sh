/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:45:15 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 08:00:29 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	dllprinthead(t_lex **head)
{
	t_lex	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putnbr(ptr->token->type);
		ft_putendl(ptr->token->data);
		if (ptr->token->type == CMD)
		{
			ft_putendl("----cmd----");
			dllprinthead(&ptr->token->command);
			ft_putendl("-----------");
		}
		ptr = ptr->next;
	}
}

void	dllprinttail(t_lex **tail)
{
	t_lex	*ptr;

	ptr = *tail;
	while (ptr->prev)
	{
		ft_putendl(ptr->token->data);
		ptr = ptr->prev;
	}
}

t_lex	*dlllastnode(t_lex **head)
{
	t_lex	*ptr;

	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

int		dlliter(t_lex **head)
{
	t_lex	*ptr;
	int		count;

	count = 0;
	ptr = *head;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
