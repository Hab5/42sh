/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stalkcursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:17 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/15 16:30:43 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void			get_cursor(int i, int j, char *answer, t_pos *pos)
{
	char		xchar[5];
	char		ychar[5];

	ft_bzero(xchar, 5);
	ft_bzero(ychar, 5);
	++i;
	while (answer[i] && answer[i] != ';')
	{
		if ((answer[i] >= '0' && answer[i] <= '9'))
			xchar[j++] = answer[i];
		++i;
	}
	xchar[j] = '\0';
	j = 0;
	++i;
	while (answer[i] && answer[i] != 'R')
	{
		if ((answer[i] >= '0' && answer[i] <= '9'))
			ychar[j++] = answer[i];
		++i;
	}
	ychar[j] = '\0';
	pos->row = ft_atoi(xchar);
	pos->column = ft_atoi(ychar);
}

void			stalk_cursor(t_pos *pos)
{
	char		*answer;
	size_t		answerlen;
	int			i;
	int			j;

	i = 1;
	j = 0;
	if (!(answer = ft_memalloc(sizeof(char) * 16)))
		return ;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &pos->termsize);
	write(0, "\x1B[6n", 5);
	answerlen = 0;
	while (answerlen < 16 - 1
		&& read(STDIN_FILENO, answer + answerlen, 1) == 1)
	{
		if (answer[answerlen++] == 'R')
			break ;
	}
	answer[answerlen] = '\0';
	get_cursor(i, j, answer, pos);
	free(answer);
}

void			get_tail(t_pos *pos)
{
	if (pos->tailcolumn < pos->termsize.ws_col)
		pos->tailcolumn++;
	if (pos->tailcolumn == pos->termsize.ws_col)
	{
		pos->tailcolumn = 0;
		if (pos->tailrow < pos->termsize.ws_row)
			pos->tailrow++;
	}
	if (pos->tailrow >= pos->termsize.ws_row)
		pos->tailrow = pos->termsize.ws_row;
}

void			savecursor(t_pos *pos)
{
	stalk_cursor(pos);
	pos->savecolumn = pos->column;
	pos->saverow = pos->row;
}

void			cursorback(t_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->savecolumn - 1, pos->saverow - 1),
																1, ft_outc);
}
