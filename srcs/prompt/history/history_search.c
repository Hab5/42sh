/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:57:27 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/26 05:12:18 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*search_to_str(t_node *input)
{
	char		buffer[4096];
	int			i;

	i = 0;
	while (input->next)
		input = input->next;
	while (input->prev)
	{
		buffer[i++] = input->key;
		input = input->prev;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

char			*search_and_print(char *input, t_pos *pos)
{
	t_node		*cursor;

	cursor = pos->history->next;
	while (cursor)
	{
		if (ft_strstr(cursor->line, input) != 0)
		{
			savecursor(pos);
			ft_putstr("\033[35m': \033[33m");
			ft_putstr(cursor->line);
			ft_putstr("\033[0m");
			cursorback(pos);
			return (cursor->line);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

int				search_keyhook(t_node **input, char buffer[])
{
	if (PRINTABLE)
	{
		ft_putstr("\033[33m");
		ft_putchar(buffer[0]);
		ft_putstr("\033[0m");
		insert(*input, buffer[0]);
	}
	if (BACKSPACE && (*input)->next)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
		ddel(input, (*input)->next);
	}
	if (CTRL_D)
		return (-1);
	if (CTRL_C)
		return (-2);
	return (0);
}

char			*input_search(t_node **input, char *passed_input, \
											t_pos *pos, int *ret)
{
	char		*current_input;
	char		*current_choice;
	char		buffer[4096];

	current_input = NULL;
	ft_bzero(buffer, 4096);
	current_choice = search_and_print(passed_input, pos);
	while (read(STDIN_FILENO, &buffer, 4095) < 4095 && \
			(PRINTABLE || BACKSPACE || CTRL_C || CTRL_D))
	{
		*ret = search_keyhook(input, buffer);
		ft_bzero(buffer, 4096);
		ft_putstr(tgetstr("cd", NULL));
		current_input = search_to_str(*input);
		current_choice = search_and_print(current_input, pos);
		ft_strdel(&current_input);
		if (*ret < 0)
			break ;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->row - 1), 1, ft_outc);
	ft_putstr(tgetstr("cd", NULL));
	while (*input)
		ddel(input, *input);
	free(passed_input);
	return (*ret < 0) ? (NULL) : (current_choice);
}

char			*prompt_search(t_node *prompt_input, t_pos *pos, int *ret)
{
	char		*passed_input;
	t_node		*input;
	int			i;

	i = 0;
	input = NULL;
	passed_input = search_to_str(prompt_input);
	raw_term_mode();
	dpush(&input, ' ');
	while (passed_input && passed_input[i])
		insert(input, passed_input[i++]);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->row - 1), 1, ft_outc);
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr("\033[35m(reverse-i-search)`\033[0m");
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(passed_input);
	return (input_search(&input, passed_input, pos, ret));
}
