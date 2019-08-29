/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:12:35 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 15:51:57 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_e_basic(t_fc *fc, t_node *lstcursor, t_pos *pos)
{
	int		fd;

	fc_check_editor(fc);
	if (lstcursor)
		fc->cmd = ft_strdup(lstcursor->line);
	fd = open("/tmp/42sh-fc.file", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fc->cmd)
		write(fd, fc->cmd, ft_strlen(fc->cmd));
	else
		write(fd, " ", 1);
	write(fd, "\n", 1);
	ft_simple_command_fc(fc->editor);
	close(fd);
	fc_e_run_command(pos);
	return (1);
}

int			fc_e_first(t_fc *fc, t_node *lstcursor, t_pos *pos, int count)
{
	fc_check_editor(fc);
	if (fc_get_index(lstcursor, count, &fc->first_index, fc->first) == -1)
		return (fc_usage(-1, fc, 2));
	if (fc->first_index > count || fc->first_index < 0)
		return (fc_usage(-1, fc, 2));
	fc_write_file(fc, lstcursor, count);
	ft_simple_command_fc(fc->editor);
	fc_e_run_command(pos);
	return (1);
}

int			fc_e_first_last(t_fc *fc, t_node *lstcursor, t_pos *pos, int count)
{
	fc_check_editor(fc);
	if (fc_get_index(lstcursor, count, &fc->first_index, fc->first) == -1)
		return (fc_usage(-1, fc, 2));
	if (fc_get_index(lstcursor, count, &fc->last_index, fc->last) == -1)
		return (fc_usage(-1, fc, 2));
	if (fc->first_index > count || fc->first_index < 0 \
		|| fc->last_index > count || fc->last_index < 0)
		return (fc_usage(-1, fc, 2));
	fc_write_file(fc, lstcursor, count);
	ft_simple_command_fc(fc->editor);
	fc_e_run_command(pos);
	return (1);
}

int			fc_e(t_fc *fc, t_pos *pos)
{
	int		count;
	t_node	*lstcursor;

	lstcursor = pos->history->next;
	count = fc_count(pos->history);
	if (!fc->first)
		if (fc_e_basic(fc, lstcursor, pos) == -1)
			return (-1);
	if (fc->first && !fc->last)
		if (fc_e_first(fc, lstcursor, pos, count) == -1)
			return (-1);
	if (fc->first && fc->last)
		if (fc_e_first_last(fc, lstcursor, pos, count) == -1)
			return (-1);
	return (1);
}
