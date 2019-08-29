/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:32:02 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/08 00:32:03 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_node		*delete_selection_left(t_node **input, t_node *lstcursor,
															t_pos *pos)
{
	while (pos->selectcount > 0)
	{
		stalk_cursor(pos);
		if (pos->column == 1)
			go_upright(pos);
		else
			ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("cd", NULL));
		if (lstcursor->next)
			ddel(input, lstcursor->next);
		pos->selectcount--;
	}
	if (lstcursor->prev != NULL)
		lstcursor = lstcursor->next;
	pos->selectcount = 0;
	return (lstcursor);
}

t_node		*delete_selection_right(t_node **input, t_node *lstcursor,
															t_pos *pos)
{
	while (pos->selectcount < 0)
	{
		stalk_cursor(pos);
		ft_putstr(tgetstr("cd", NULL));
		if (pos->column == pos->termsize.ws_col)
			go_downleft(pos);
		lstcursor = lstcursor->prev;
		ddel(input, lstcursor->next);
		pos->selectcount++;
	}
	if (lstcursor->next != NULL)
		lstcursor = lstcursor->next;
	pos->selectcount = 0;
	return (lstcursor);
}

t_node		*delete_selection(t_node **input, t_node *lstcursor, t_pos *pos)
{
	stalk_cursor(pos);
	ft_putstr(tgetstr("ei", NULL));
	if (pos->selectcount > 0)
		lstcursor = delete_selection_left(input, lstcursor, pos);
	if (pos->selectcount < 0)
		lstcursor = delete_selection_right(input, lstcursor, pos);
	ft_putstr(tgetstr("im", NULL));
	pos->selection = 0;
	lstcursor = find_tail(lstcursor, pos);
	return (lstcursor);
}
