/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:37 by aleduc            #+#    #+#             */
/*   Updated: 2019/04/17 17:01:21 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node		*anchor_selection(t_node *lstcursor, t_pos *pos, int direction)
{
	ft_putstr(tgetstr("ei", NULL));
	if (direction == 0 && lstcursor->prev)
	{
		pos->selectcount++;
		ft_putchar(lstcursor->key);
		lstcursor = lstcursor->prev;
	}
	if (direction == 1 && lstcursor->next)
	{
		pos->selectcount--;
		ft_putstr(tgetstr("le", NULL));
		ft_putchar(lstcursor->next->key);
		lstcursor = lstcursor->next;
		ft_putstr(tgetstr("le", NULL));
	}
	ft_putstr(tgetstr("im", NULL));
	return (lstcursor);
}

t_node		*shift_left(t_node *lstcursor, char buffer[], t_pos *pos)
{
	if (SHIFT_LEFT && lstcursor->next)
	{
		pos->selectcount--;
		ft_putstr(tgetstr("ei", NULL));
		ft_putstr(tgetstr("mr", NULL));
		if (pos->column != 1)
		{
			ft_putstr(tgetstr("le", NULL));
			ft_putchar(lstcursor->next->key);
			lstcursor = lstcursor->next;
			ft_putstr(tgetstr("le", NULL));
		}
		if (pos->column == 1)
		{
			go_upright(pos);
			ft_putchar(lstcursor->next->key);
			lstcursor = lstcursor->next;
		}
		ft_putstr(tgetstr("me", NULL));
		ft_putstr(tgetstr("im", NULL));
	}
	return (lstcursor);
}

t_node		*shift_right(t_node *lstcursor, char buffer[], t_pos *pos)
{
	if (SHIFT_RIGHT && lstcursor->prev)
	{
		pos->selectcount++;
		ft_putstr(tgetstr("ei", NULL));
		ft_putstr(tgetstr("mr", NULL));
		if (pos->column != pos->termsize.ws_col)
		{
			ft_putchar(lstcursor->key);
			lstcursor = lstcursor->prev;
		}
		if (pos->column == pos->termsize.ws_col)
		{
			ft_putchar(lstcursor->key);
			lstcursor = lstcursor->prev;
			go_downleft(pos);
		}
		ft_putstr(tgetstr("me", NULL));
		ft_putstr(tgetstr("im", NULL));
	}
	return (lstcursor);
}

t_node		*alt_bindings(t_node **input, t_node *lstcursor, char buffer[],
																t_pos *pos)
{
	if ((ALT_C || ALT_X) && pos->selection == 1)
		copy_selection(lstcursor, pos);
	if (ALT_X && pos->selection == 1)
	{
		lstcursor = delete_selection(input, lstcursor, pos);
		redraw(pos, lstcursor);
	}
	if (ALT_V && pos->clipboard != NULL)
		lstcursor = paste_clipboard(input, lstcursor, pos);
	return (lstcursor);
}

t_node		*selectmode(t_node **input, t_node *lstcursor, char buffer[],
																t_pos *pos)
{
	if (SHIFT_LEFT || SHIFT_RIGHT)
	{
		if (pos->selection == 0)
			pos->selection = 1;
		if (pos->selectcount >= 0 && SHIFT_RIGHT)
			lstcursor = shift_right(lstcursor, buffer, pos);
		if (pos->selectcount < 0 && SHIFT_RIGHT)
			lstcursor = anchor_selection(lstcursor, pos, 0);
		if (pos->selectcount <= 0 && SHIFT_LEFT)
			lstcursor = shift_left(lstcursor, buffer, pos);
		if (pos->selectcount > 0 && SHIFT_LEFT)
			lstcursor = anchor_selection(lstcursor, pos, 1);
	}
	lstcursor = alt_bindings(input, lstcursor, buffer, pos);
	if (!SHIFT_LEFT && !SHIFT_RIGHT && !ALT_C && !ALT_X && !ALT_V
											&& pos->selection == 1)
		lstcursor = undo_selection(lstcursor, pos);
	return (lstcursor);
}
