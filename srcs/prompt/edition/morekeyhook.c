/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morekeyhook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:18:42 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/26 05:00:34 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "env.h"
#include "builtins.h"

extern t_ht_hash	*g_hash_table;
extern t_ht_hash	*g_alias_table;

t_node				*backwardmod(t_node *lstcursor, t_pos *pos)
{
	if (lstcursor->next && lstcursor->key != ' ' && lstcursor->next->key == ' ')
	{
		stalk_cursor(pos);
		if (pos->column == 1)
			go_upright(pos);
		else
			ft_putstr(tgetstr("le", NULL));
		lstcursor = lstcursor->next;
	}
	if (lstcursor->next && lstcursor->key == ' ')
	{
		while (lstcursor->next && lstcursor->key == ' ')
		{
			stalk_cursor(pos);
			if (pos->column == 1)
				go_upright(pos);
			else
				ft_putstr(tgetstr("le", NULL));
			lstcursor = lstcursor->next;
		}
	}
	return (lstcursor);
}

t_node				*backwardjump(t_node *lstcursor, char buffer[], t_pos *pos)
{
	if (PG_DOWN)
	{
		lstcursor = backwardmod(lstcursor, pos);
		while (lstcursor->next && lstcursor->next->key != ' ')
		{
			stalk_cursor(pos);
			if (pos->column == 1)
				go_upright(pos);
			else
				ft_putstr(tgetstr("le", NULL));
			lstcursor = lstcursor->next;
		}
	}
	return (lstcursor);
}

t_node				*forwardjump(t_node *lstcursor, char buffer[], t_pos *pos)
{
	if (PG_UP)
	{
		while (lstcursor->prev && lstcursor->key != ' ')
		{
			lstcursor = lstcursor->prev;
			stalk_cursor(pos);
			if (pos->column == pos->termsize.ws_col)
				go_downleft(pos);
			else
				ft_putstr(tgetstr("nd", NULL));
		}
		while (lstcursor->prev && lstcursor->key == ' ')
		{
			lstcursor = lstcursor->prev;
			if (pos->column == pos->termsize.ws_col)
				go_downleft(pos);
			else
				ft_putstr(tgetstr("nd", NULL));
		}
	}
	return (lstcursor);
}

t_node				*ctrl_r(t_node *lstcursor, t_node **input, t_pos *pos)
{
	int				i;
	char			*search_result;
	t_node			*new;
	int				ret;

	i = 0;
	ret = 0;
	new = NULL;
	if ((search_result = prompt_search(*input, pos, &ret)) != NULL)
	{
		dpush(&new, ' ');
		while (search_result && search_result[i])
			insert(new, search_result[i++]);
		while (*input)
			ddel(input, *input);
		*input = new;
	}
	if (ret == -1)
		while ((*input)->next)
			ddel(input, *input);
	lstcursor = *input;
	print_prompt();
	dprintlist(*input, 0);
	return (lstcursor);
}

t_node				*ctrl_n_friends(t_node *lstcursor, t_node **input,\
									char buffer[], t_pos *pos)
{
	if (CTRL_D && !(*input)->next && pos->multiline != 1)
	{
		bt_exit(NULL, pos, NULL);
		print_prompt();
	}
	if (CTRL_C)
	{
		while (((*input)->next) != NULL)
			ddel(input, *input);
		pos->stop = 1;
		pos->multiline = 0;
		travel_to_last(lstcursor, pos);
		ft_putchar('\n');
		gest_return(130);
	}
	if (CTRL_R)
	{
		lstcursor = ctrl_r(lstcursor, input, pos);
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("cd", NULL));
		stalk_cursor(pos);
	}
	return (lstcursor);
}
