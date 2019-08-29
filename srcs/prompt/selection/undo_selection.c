/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:32:10 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/08 00:32:45 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		undo_selection_left(t_node *cursorcpy, t_pos *pos)
{
	while (pos->selectcount <= 0)
	{
		stalk_cursor(pos);
		ft_putchar(cursorcpy->key);
		if (pos->column == pos->termsize.ws_col)
			go_downleft(pos);
		cursorcpy = cursorcpy->prev;
		pos->selectcount++;
	}
	pos->selectcount = 0;
}

void		undo_selection_right(t_node *cursorcpy, t_pos *pos)
{
	while (pos->selectcount > 0)
	{
		stalk_cursor(pos);
		if (pos->column != 1)
			ft_putstr(tgetstr("le", NULL));
		if (pos->column == 1)
			go_upright(pos);
		cursorcpy = cursorcpy->next;
		pos->selectcount--;
	}
	while (cursorcpy->prev != NULL)
	{
		ft_putchar(cursorcpy->key);
		cursorcpy = cursorcpy->prev;
	}
	pos->selectcount = 0;
}

t_node		*undo_selection(t_node *lstcursor, t_pos *pos)
{
	t_node	*cursorcpy;

	cursorcpy = lstcursor;
	savecursor(pos);
	ft_putstr(tgetstr("ei", NULL));
	if (pos->selectcount < 0)
		undo_selection_left(cursorcpy, pos);
	if (pos->selectcount > 0)
		undo_selection_right(cursorcpy, pos);
	ft_putstr(tgetstr("im", NULL));
	pos->selection = 0;
	cursorback(pos);
	return (lstcursor);
}
