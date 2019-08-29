/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:06:15 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 19:48:22 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_usage(int return_value, t_fc *fc, int error)
{
	if (error == 1)
		ft_dprintf(2, \
		"fc: usage: fc [-e(s)] [ename] [first[last]]\n\t   \
		fc [-l(nr)] [first[last]]\n\t   \
		fc -s [pat=rep] [cmd]\n");
	if (error == 2)
		ft_dprintf(2, "42sh: fc: history specification out of range\n");
	ft_strdel(&fc->pat_rep);
	ft_strdel(&fc->first);
	ft_strdel(&fc->last);
	ft_strdel(&fc->editor);
	ft_strdel(&fc->cmd);
	return (return_value);
}

void		fc_debug(t_fc *fc)
{
	ft_dprintf(1, "l = %d || n = %d || r = %d || e = %d || s = %d\n",
	fc->flags[0], fc->flags[1], fc->flags[2], fc->flags[3], fc->flags[4]);
	if (fc->first)
		ft_dprintf(1, "first = %s\n", fc->first);
	if (fc->last)
		ft_dprintf(1, "last = %s\n", fc->last);
	if (fc->first_index)
		ft_dprintf(1, "first_index = %d\n", fc->first_index);
	if (fc->last_index)
		ft_dprintf(1, "last_index = %d\n", fc->last_index);
	if (fc->editor)
		ft_dprintf(1, "editor = %s\n", fc->editor);
	if (fc->cmd)
		ft_dprintf(1, "cmd = %s\n", fc->cmd);
	if (fc->pat_rep)
		ft_dprintf(1, "pat_rep = %s\n", fc->pat_rep);
}

int			fc_count(t_node *history)
{
	t_node	*lstcursor;
	int		count;

	count = 1;
	lstcursor = history;
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && lstcursor->prev->prev)
	{
		count++;
		lstcursor = lstcursor->prev;
	}
	return (count);
}

int			fc_get_index_len(t_node *lstcursor, char *fc_first_last)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (lstcursor->next && (ret = ft_strnequ(fc_first_last, \
				lstcursor->line, ft_strlen(fc_first_last))) != 1)
	{
		i++;
		lstcursor = lstcursor->next;
	}
	if (ret != 1)
		return (-1);
	else
		return (i);
}

int			fc_get_index(t_node *lstcursor, int count, int *fc_index, \
													char *fc_first_last)
{
	int		i;

	i = 0;
	if (fc_first_last[0] == '-')
	{
		*fc_index = count - ft_atoi(fc_first_last + 1);
		if (*fc_index > count)
			return (-1);
		else
			return (1);
	}
	if (ft_isnumbers(fc_first_last) == 1)
	{
		*fc_index = ft_atoi(fc_first_last);
		if (*fc_index > count)
			return (-1);
		else
			return (1);
	}
	if ((i = fc_get_index_len(lstcursor, fc_first_last)) == -1)
		return (-1);
	*fc_index = count - i;
	return (1);
}
