/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 21:26:12 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 23:38:59 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		hist_rep_delstruct(t_hist_rep *to_del)
{
	if (!to_del)
		return ;
	hist_rep_delstruct(to_del->next);
	ft_strdel(&(to_del->base));
	to_del->next = NULL;
	to_del->value = NULL;
	free(to_del);
	to_del = NULL;
	return ;
}

int			hist_rep_getexp(char *input)
{
	int		i;

	i = 1;
	if (input[i] == '-' || ft_isdigit(input[i]))
	{
		++i;
		while (input && ft_isdigit(input[i]))
			++i;
		return (i);
	}
	else if (input[i] == '!')
		return (++i);
	while (input && input[i] && input[i] != ' ' && input[i] != '\t'
			&& input[i] != ';' && input[i] != '|' && input[i] != '&'
			&& input[i] != '(' && input[i] != ')' && input[i] != '<'
			&& input[i] != '>')
		++i;
	return (i);
}

int			hist_rep_isvalid(char *input)
{
	if (input[0] != '!')
		return (0);
	else if (input[1] == ' ' || input[1] == '\t' || input[1] == '\0'
			|| input[1] == '=' || input[1] == '%' || input[1] == '\n')
		return (0);
	return (1);
}

int			hist_rep_isbslashed(char *input, int i, int expand)
{
	int		isbsl;

	isbsl = 0;
	if (expand > 0)
		return (1);
	while (i > -1)
	{
		if (input[i] != '\\')
			return (isbsl);
		if (isbsl == 0)
			isbsl = 1;
		else if (isbsl == 1)
			isbsl = 0;
		--i;
	}
	return (isbsl);
}
