/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:21:01 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 19:43:28 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_lr_basic(t_fc *fc, t_node *lstcursor, int count, int i)
{
	i = 1;
	if (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor && i <= 15)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", count - i, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		i++;
		lstcursor = lstcursor->next;
	}
	return (1);
}

int			fc_l_basic(t_fc *fc, t_node *lstcursor, int count, int i)
{
	if (FC_R)
		return (fc_lr_basic(fc, lstcursor, count, i));
	while (lstcursor->next && i++ < 14)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && lstcursor->prev->prev)
	{
		if (!FC_N)
		{
			if (count <= 15)
				ft_dprintf(1, "%d	%s\n", count - (i) - 1, lstcursor->line);
			else
				ft_dprintf(1, "%d	%s\n", count - (i), lstcursor->line);
		}
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		i--;
		lstcursor = lstcursor->prev;
	}
	return (1);
}

int			fc_lr_first_nb(t_fc *fc, t_node *lstcursor, int count, int i)
{
	while (lstcursor->next && count >= i)
	{
		lstcursor = lstcursor->next;
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", count--, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
	}
	return (1);
}

int			fc_l_first_nb(t_fc *fc, t_node *lstcursor, int count, int i)
{
	t_node	*backup_cursor;

	backup_cursor = lstcursor;
	i = 1;
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && i < ft_atoi(fc->first))
	{
		lstcursor = lstcursor->prev;
		if (!lstcursor->prev && i < ft_atoi(fc->first))
			return (fc_usage(-1, fc, 2));
		i++;
	}
	if (FC_R)
		return (fc_lr_first_nb(fc, backup_cursor, count - 1, i));
	while (lstcursor->prev && lstcursor->prev->prev)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", i++, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		lstcursor = lstcursor->prev;
	}
	return (1);
}

int			fc_lr_first_word(t_fc *fc, t_node *lstcursor, int count, int i)
{
	if (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->next && i-- >= 0)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", count-- + 1, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		lstcursor = lstcursor->next;
	}
	return (1);
}
