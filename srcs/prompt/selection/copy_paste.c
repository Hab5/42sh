/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:30:30 by mbellaic          #+#    #+#             */
/*   Updated: 2019/05/15 16:38:30 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		copy_selection_left(t_node *cursorcpy, t_pos *pos, int count)
{
	int		i;

	i = 0;
	while (count <= -1)
	{
		pos->clipboard[i] = cursorcpy->key;
		i++;
		count++;
		cursorcpy = cursorcpy->prev;
	}
	pos->clipboard[i] = '\0';
}

void		copy_selection_right(t_node *cursorcpy, t_pos *pos, int count)
{
	int		i;

	i = 0;
	while (count >= 0)
	{
		pos->clipboard[i] = cursorcpy->key;
		i++;
		count--;
		cursorcpy = cursorcpy->next;
	}
	pos->clipboard[i] = '\0';
	reverse_str(pos->clipboard);
}

void		copy_selection(t_node *lstcursor, t_pos *pos)
{
	int		count;
	t_node	*cursorcpy;

	if (pos->clipboard != NULL)
		free(pos->clipboard);
	if (!(pos->clipboard = (char *)malloc(sizeof(char) * 4096)))
		return ;
	cursorcpy = lstcursor;
	count = pos->selectcount;
	if (count < 0)
		copy_selection_left(cursorcpy, pos, count);
	if (count > 0)
		copy_selection_right(cursorcpy, pos, count);
}

t_node		*paste_clipboard(t_node **input, t_node *lstcursor, t_pos *pos)
{
	int		i;

	i = 0;
	if (pos->selection == 1)
	{
		lstcursor = delete_selection(input, lstcursor, pos);
		redraw(pos, lstcursor);
		pos->selection = 0;
	}
	while (pos->clipboard[i])
	{
		insert(lstcursor, pos->clipboard[i]);
		ft_putchar(pos->clipboard[i]);
		i++;
	}
	lstcursor = find_tail(lstcursor, pos);
	return (lstcursor);
}
