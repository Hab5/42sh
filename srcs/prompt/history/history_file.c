/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:32:42 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 21:59:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "env.h"

void		history_file(t_node *history)
{
	t_node	*cursor;
	int		fd;

	cursor = history;
	fd = open("/tmp/.history", O_RDWR | O_CREAT, 0666);
	while (cursor->next)
		cursor = cursor->next;
	while (cursor->prev)
	{
		write(fd, cursor->line, ft_strlen(cursor->line));
		write(fd, "\n", 1);
		cursor = cursor->prev;
	}
	close(fd);
}

void		file_to_history(t_pos *pos)
{
	int		fd;
	char	*history_line;

	history_line = NULL;
	fd = open("/tmp/.history", O_RDWR | O_CREAT, 0666);
	inserthistory(pos->history, " ", pos);
	while (get_next_line(fd, &history_line) > 0)
	{
		inserthistory(pos->history, history_line, pos);
		pos->historysum++;
		ft_strdel(&history_line);
	}
	if (verif_close(fd))
		close(fd);
}

char		*history_no_double(t_pos *pos)
{
	if (pos->history->next)
		return (pos->history->next->line);
	else
		return (NULL);
}
