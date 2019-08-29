/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursortools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:17:01 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/12 17:17:10 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		get_startingpos(t_pos *pos)
{
	stalk_cursor(pos);
	pos->startcolumn = pos->column;
	pos->startrow = pos->row;
	pos->tailcolumn = pos->startcolumn;
	pos->tailrow = pos->startrow;
}

t_node		*travel_to_last(t_node *lstcursor, t_pos *pos)
{
	size_t	i;

	i = pos->row;
	if (pos->row < pos->tailrow)
	{
		while (i++ < pos->tailrow)
			ft_putstr(tgetstr("do", NULL));
	}
	return (lstcursor);
}

void		go_upright(t_pos *pos)
{
	char	*move;

	stalk_cursor(pos);
	move = tgetstr("cm", NULL);
	tputs(tgoto(move, pos->termsize.ws_col - 1, pos->row - 2), 1, ft_outc);
	ft_putstr(tgetstr("nd", NULL));
	stalk_cursor(pos);
}

void		go_downleft(t_pos *pos)
{
	char	*move;

	stalk_cursor(pos);
	move = tgetstr("cm", NULL);
	tputs(tgoto(move, 0, pos->row), 1, ft_outc);
	stalk_cursor(pos);
}

int			ft_outc(int c)
{
	return (write(1, &c, 1));
}
