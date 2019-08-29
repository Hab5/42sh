/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:26:45 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 00:48:06 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		reset_multi(t_pos *pos)
{
	stalk_cursor(pos);
	pos->tailcolumn = pos->column;
	pos->tailrow = pos->tailrow;
	pos->selection = 0;
	pos->selectcount = 0;
	pos->inputlen = 0;
	get_startingpos(pos);
}

t_node		*try_to_match(t_node *cursor, t_integrity *count, char type)
{
	t_node	*cursorcpy;

	cursorcpy = cursor;
	cursor = cursor->prev;
	while (cursor && cursor->prev)
	{
		if (cursor->key == type)
		{
			if (cursor->next->key != '\\' && type == '"')
				count->dquote++;
			if (type == '\'')
				count->quote++;
			return (cursor);
		}
		cursor = cursor->prev;
	}
	return (cursorcpy);
}

void		key_occurence(t_node *cursor, t_integrity *count)
{
	while (cursor)
	{
		if (cursor->key == '"' && (count->quote % 2) == 0)
		{
			if (!cursor->next \
			|| (cursor->next && !(cursor->next->key == '\\')))
			{
				count->dquote++;
				cursor = try_to_match(cursor, count, '"');
			}
		}
		if (cursor->key == '\'' && (count->dquote % 2) == 0)
		{
			if (!cursor->next \
			|| (cursor->next && !(cursor->next->key == '\\')))
			{
				count->quote++;
				cursor = try_to_match(cursor, count, '\'');
			}
		}
		cursor = cursor->prev;
	}
}

void		dquote(t_multi *lstcursor, t_multi **multi, t_pos *pos)
{
	lstcursor = *multi;
	multi_push(multi);
	lstcursor = lstcursor->prev;
	lstcursor->input = NULL;
	dpush(&lstcursor->input, ' ');
	ft_putstr("dquote>");
	read_input(&lstcursor->input, pos);
}

void		quote(t_multi *lstcursor, t_multi **multi, t_pos *pos)
{
	lstcursor = *multi;
	multi_push(multi);
	lstcursor = lstcursor->prev;
	lstcursor->input = NULL;
	dpush(&lstcursor->input, ' ');
	ft_putstr("quote>");
	read_input(&lstcursor->input, pos);
}
