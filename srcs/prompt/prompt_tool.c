/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 03:56:27 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 07:42:56 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "builtins.h"
#include "env.h"

int				count_escape_backslash(t_node *input)
{
	int			i;
	t_node		*lstcursor;

	lstcursor = input->next;
	i = 1;
	while (lstcursor->next && lstcursor->next->key == '\\')
	{
		i++;
		lstcursor = lstcursor->next;
	}
	return (i);
}

int				check_backslash(t_node *input, t_multi **multi, t_pos *pos,\
														t_integrity *count)
{
	t_multi		*lstcursor;

	if (input->next && input->next->key == '\\'
		&& (count_escape_backslash(input) % 2) == 1)
	{
		lstcursor = *multi;
		multi_push(multi);
		lstcursor = lstcursor->prev;
		lstcursor->input = NULL;
		dpush(&lstcursor->input, ' ');
		ft_putstr("backslash>");
		read_input(&lstcursor->input, pos);
		key_occurence(lstcursor->input, count);
		return (-1);
	}
	return (1);
}

void			line_to_history(char **inputstr, t_pos *pos)
{
	*inputstr = history_replace(*inputstr, pos);
	if (inputstr && pos->stop != 1 \
		&& (ft_strequ(*inputstr, history_no_double(pos))) == 0)
		inserthistory(pos->history, *inputstr, pos);
}
