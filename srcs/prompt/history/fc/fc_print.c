/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:11:51 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 18:12:46 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_print_first_last(t_fc *fc, t_node *lstcursor, int i)
{
	i = 0;
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && lstcursor->prev->prev && ++i < fc->first_index)
		lstcursor = lstcursor->prev;
	while (lstcursor->prev && lstcursor->prev->prev && i <= fc->last_index)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", i, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		i++;
		lstcursor = lstcursor->prev;
	}
	return (1);
}

int			fc_print_last_first(t_fc *fc, t_node *lstcursor, int i)
{
	i = 0;
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	while (lstcursor->prev && ++i < fc->first_index)
		lstcursor = lstcursor->prev;
	while (lstcursor && i >= fc->last_index)
	{
		if (!FC_N)
			ft_dprintf(1, "%d	%s\n", i, lstcursor->line);
		else
			ft_dprintf(1, "%s\n", lstcursor->line);
		i--;
		lstcursor = lstcursor->next;
	}
	return (1);
}
