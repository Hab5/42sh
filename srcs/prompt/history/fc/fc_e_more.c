/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:14:47 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 15:51:55 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_check_editor(t_fc *fc)
{
	if (!fc->editor)
	{
		if ((fc->editor = value_line_path("FCEDIT", 0)))
			;
		else if ((fc->editor = value_line_path("EDITOR", 0)))
			;
		else
			fc->editor = ft_strdup("ed");
	}
	return (0);
}

void		fc_filter_history(t_fc *fc, t_pos *pos)
{
	if (FC_E || FC_S || FC_NO_FLAGS)
	{
		free(pos->history->next->line);
		ddel(&pos->history, pos->history->next);
	}
}

int			fc_e_run_command(t_pos *pos)
{
	char	*command;
	int		fd;

	fd = open("/tmp/42sh-fc.file", O_RDONLY, 0666);
	while (get_next_line(fd, &command) > 0)
	{
		inserthistory(pos->history, command, pos);
		pos->historysum++;
		ft_printf("\n\033[33;01m%s\033[00m\n", command);
		run(command, pos);
	}
	close(fd);
	return (1);
}

int			fc_write_last_first(t_fc *fc, t_node *lstcursor, int count)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("/tmp/42sh-fc.file", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (lstcursor->next && ++i <= count - fc->first_index)
		lstcursor = lstcursor->next;
	i = fc->first_index;
	while (lstcursor->next && i-- >= fc->last_index)
	{
		ft_dprintf(fd, "%s\n", lstcursor->line);
		lstcursor = lstcursor->next;
	}
	return (1);
}

int			fc_write_file(t_fc *fc, t_node *lstcursor, int count)
{
	int		fd;
	int		i;

	i = 0;
	if (fc->last_index && fc->last_index < fc->first_index)
	{
		fc_write_last_first(fc, lstcursor, count);
		return (1);
	}
	fd = open("/tmp/42sh-fc.file", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && ++i < fc->first_index)
		lstcursor = lstcursor->prev;
	i = fc->first_index;
	if (fc->first_index && !fc->last_index)
		ft_dprintf(fd, "%s\n", lstcursor->line);
	if (fc->first_index && fc->last_index)
		while (lstcursor->prev && lstcursor->prev->prev \
								&& i++ <= fc->last_index)
		{
			ft_dprintf(fd, "%s\n", lstcursor->line);
			lstcursor = lstcursor->prev;
		}
	return (1);
}
