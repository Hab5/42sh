/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 21:58:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "env.h"

char		*heredoc_string(t_node *lstcursor)
{
	char	*temp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (lstcursor->next)
	{
		len++;
		lstcursor = lstcursor->next;
	}
	if (!(temp = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (lstcursor->prev)
	{
		temp[i] = lstcursor->key;
		lstcursor = lstcursor->prev;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void		test(t_node **input, char *temp)
{
	int i;

	i = 0;
	while (temp[i])
		dpush(input, temp[i++]);
	dpush(input, temp[i]);
}

int			check_heredoc(t_node **input, char *heredoc)
{
	char	*temp;
	t_node	*lstcursor;
	t_node	*new;

	lstcursor = *input;
	temp = heredoc_string(lstcursor);
	parser_var_simple(&temp, 0);
	new = NULL;
	test(&new, temp);
	while (lstcursor)
		ddel(&lstcursor, lstcursor);
	*input = new;
	if (ft_strcmp(heredoc, temp) == 0)
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (-1);
}

int			input_heredoc(t_multi *lstcursor, t_multi **multi, t_pos *pos,
																char *heredoc)
{
	lstcursor = *multi;
	multi_push(multi);
	lstcursor = lstcursor->prev;
	lstcursor->input = NULL;
	dpush(&lstcursor->input, ' ');
	ft_putstr("heredoc>");
	read_input(&lstcursor->input, pos);
	return (check_heredoc(&lstcursor->input, heredoc));
}

char		*heredoc(char *heredoc, t_pos *pos)
{
	t_multi	*multi;
	t_multi	*lstcursor;
	char	*input;

	multi = NULL;
	input = NULL;
	lstcursor = NULL;
	raw_term_mode();
	multi_push(&multi);
	multi->input = NULL;
	dpush(&multi->input, ' ');
	init_heredoc(pos);
	parser_var_simple(&heredoc, 1);
	while (((input_heredoc(lstcursor, &multi, pos, heredoc)) < 0)
			&& pos->stop != 1)
		init_heredoc(pos);
	input = lst_to_str(&multi, input);
	ddellist(multi);
	(pos->stop == 1) ? ft_strdel(&input) : 0;
	(pos->stop == 1) ? pos->stop = 0 : 0;
	pos->multiline = 0;
	default_term_mode();
	ft_strdel(&heredoc);
	return (input);
}
