/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:09:20 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 19:50:17 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_l_first_word(t_fc *fc, t_node *lstcursor, int count, int i)
{
	t_node	*backup_cursor;
	int		ret;

	i = -1;
	ret = 0;
	backup_cursor = lstcursor;
	while (lstcursor->next && \
	(ret = ft_strnequ(fc->first, lstcursor->line, ft_strlen(fc->first))) != 1)
	{
		i++;
		lstcursor = lstcursor->next;
	}
	if (ret != 1)
		return (fc_usage(-1, fc, 2));
	if (FC_R)
		return (fc_lr_first_word(fc, backup_cursor, count - 2, i));
	while (lstcursor->prev && lstcursor->prev->prev)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", count - (i--) - 1, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		lstcursor = lstcursor->prev;
	}
	return (1);
}

int			fc_l_first(t_fc *fc, t_node *lstcursor, int count, int i)
{
	int		first_nb;

	first_nb = ft_isnumbers(fc->first);
	if (first_nb == 1 && (fc_l_first_nb(fc, lstcursor, count, i) == -1))
		return (-1);
	else if (first_nb != 1 && (fc_l_first_word(fc, lstcursor, count, i) == -1))
		return (-1);
	return (1);
}

int			fc_l_first_last(t_fc *fc, t_node *lstcursor, int count, int i)
{
	if (fc_get_index(lstcursor, count, &fc->first_index, fc->first) == -1)
		return (fc_usage(-1, fc, 2));
	if (fc_get_index(lstcursor, count, &fc->last_index, fc->last) == -1)
		return (fc_usage(-1, fc, 2));
	if (fc->first_index <= fc->last_index && !FC_R)
		return (fc_print_first_last(fc, lstcursor, i));
	if (fc->first_index >= fc->last_index && !FC_R)
		return (fc_print_last_first(fc, lstcursor->next, i));
	if (fc->first_index <= fc->last_index && FC_R)
	{
		ft_swap(&fc->first_index, &fc->last_index);
		return (fc_print_last_first(fc, lstcursor, i));
	}
	if (fc->first_index >= fc->last_index && FC_R)
	{
		ft_swap(&fc->first_index, &fc->last_index);
		return (fc_print_first_last(fc, lstcursor, i));
	}
	return (1);
}

int			fc_l_minus(t_fc *fc, int count)
{
	char	*temp;

	if (fc->first[0] == '-')
	{
		temp = ft_itoa(count - ft_atoi(fc->first + 1));
		free(fc->first);
		fc->first = ft_strdup(temp);
		free(temp);
		fc->flags[2] ^= 1;
		if (ft_atoi(fc->first) > count)
			return (-1);
		else
			return (1);
	}
	return (0);
}

int			fc_l(t_fc *fc, t_pos *pos)
{
	int		count;
	int		i;
	t_node	*lstcursor;

	lstcursor = pos->history->next;
	count = fc_count(pos->history);
	i = -1;
	if (!fc->first)
		fc_l_basic(fc, lstcursor, count, i);
	else if (fc->first && !fc->last)
	{
		if (fc_l_minus(fc, count) == -1)
			return (fc_usage(-1, fc, 2));
		if (fc_l_first(fc, lstcursor, count, i) == -1)
			return (-1);
	}
	else if (fc->first && fc->last)
		if (fc_l_first_last(fc, lstcursor, count, i) == -1)
			return (-1);
	return (0);
}
