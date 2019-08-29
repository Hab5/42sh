/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 20:59:45 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		removebackslash(char **line)
{
	int		i;
	int		expand;

	i = 0;
	expand = 0;
	if ((!line) || (!(*line)))
		return ;
	if (**line == '\\' && *(*line + 1) != '\n')
		return ;
	while ((*line) && (*line)[i])
	{
		expand = manage_is_quote((*line), i, expand);
		if ((*line)[i] == '\\' && expand > 0)
		{
			if (ft_remove_element(line, i, expand))
				return ;
		}
		else if ((*line)[i] == '\\' && expand == 0)
		{
			if (ft_remove_element(line, i, expand))
				return ;
		}
		else
			++i;
	}
}

void		remove_quote_bis(int *i, char **line)
{
	ft_strremove_char(line, *i);
	*i = ft_chr_index((*line), '\'');
	ft_strremove_char(line, (*i)--);
}

void		remove_quote_line_first(char **line)
{
	int	i;
	int	expand;

	i = 0;
	expand = 0;
	if ((!line) || (!(*line)))
		return ;
	while ((*line)[i])
	{
		expand = manage_is_quote((*line), i, expand);
		if (expand <= 0 && (*line)[i] == '\\')
		{
			ft_strremove_char(line, i);
			if ((*line)[i] && (*line)[i] == '\n')
				ft_strremove_char(line, i);
			else
				++i;
		}
		else if ((*line)[i] && expand > 0 && (*line)[i] == '\'')
			remove_quote_bis(&i, line);
		else if ((*line)[i] && expand <= 0 && (*line)[i] == '"')
			ft_strremove_char(line, i);
		else
			++i;
	}
}

void		remove_quote_line(char **line)
{
	remove_quote_line_first(line);
}

void		remove_quote(char ***value)
{
	int	i;

	i = -1;
	while ((*value)[++i])
	{
		remove_quote_line(&((*value)[i]));
		removebackslash(&((*value)[i]));
	}
}
