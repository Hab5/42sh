/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:13:03 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 15:56:35 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

char		*fc_rep(char *str, char *pat_rep)
{
	char	buffer[4096];
	char	pat[4096];
	char	rep[4096];
	int		i;
	char	*p;

	i = 0;
	while (pat_rep[i] != '=')
		i++;
	ft_strncpy(pat, pat_rep, i);
	ft_strcpy(rep, pat_rep + i + 1);
	p = NULL;
	if (!(p = ft_strstr(str, pat)))
		return (str);
	ft_strncpy(buffer, str, p - str);
	buffer[p - str] = '\0';
	ft_strcpy(buffer + (p - str), rep);
	return (ft_strjoin(buffer, p + (ft_strlen(pat))));
}

int			fc_s_all(t_fc *fc, t_node *lstcursor, t_pos *pos, int count)
{
	int		i;
	char	*command;

	i = 0;
	command = NULL;
	if (fc_get_index(lstcursor, count, &fc->first_index, fc->first) == -1)
		return (fc_usage(-1, fc, 2));
	while (lstcursor && lstcursor->next && ++i < count - fc->first_index)
		lstcursor = lstcursor->next;
	if (lstcursor->line && fc->pat_rep && !ft_strequ(fc->pat_rep, "--"))
		command = fc_rep(lstcursor->line, fc->pat_rep);
	else
		command = ft_strdup(lstcursor->line);
	ft_printf("\n\033[33;01m%s\033[00m\n", command);
	if (command)
		inserthistory(pos->history, command, pos);
	run(command, pos);
	return (1);
}

int			fc_s(t_fc *fc, t_pos *pos)
{
	int		count;
	t_node	*lstcursor;

	lstcursor = pos->history->next;
	count = fc_count(pos->history);
	if (fc_s_all(fc, lstcursor, pos, count) == -1)
		return (-1);
	return (1);
}
