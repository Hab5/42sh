/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 21:58:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "env.h"

void		init_heredoc(t_pos *pos)
{
	pos->multiline = 1;
	pos->nblines = 0;
	pos->currentline = 0;
	pos->selection = 0;
	pos->selectcount = 0;
	pos->inputlen = 0;
	pos->savecolumn = 0;
	pos->saverow = 0;
	pos->startrow = 0;
	pos->startcolumn = 0;
	pos->tailcolumn = 0;
	pos->tailrow = 0;
	pos->stop = 0;
}
