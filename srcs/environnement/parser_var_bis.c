/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 20:41:10 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		copy_value(char *src, char **dst, int start, int end)
{
	char	*tmp;
	char	*stock;

	stock = ft_strsub(src, start, end - start);
	tmp = ft_strjoin(*dst, stock);
	ft_strdel(&(*dst));
	ft_strdel(&stock);
	(*dst) = tmp ? tmp : NULL;
}

char		*search_var(char *src)
{
	int		i;
	int		len;
	int		last;
	char	*dst;

	i = -1;
	last = 0;
	len = ft_strlen(src);
	dst = ft_strdup("");
	while (++i < len)
	{
		if (src[i] == '$' || (i == 0 && src[i] == '~'))
		{
			if (i != last)
				copy_value(src, &dst, last, i);
			if (src[i] == '~' && i == 0)
				i = manage_home(src, &dst, i) - 1;
			else
				i = apply_rules(src, &dst, i);
			last = i + 1;
		}
	}
	if (i != last)
		copy_value(src, &dst, last, i);
	return (dst);
}

int			manage_is_quote(char *value, int index, int expand)
{
	char	c;

	c = value[index];
	if (index - 1 > -1 && value[index - 1] == '\\')
		return (expand);
	if (c == '\'')
	{
		if (expand == 0)
			return (expand + 1);
		if (expand > 0)
			return (expand - 1);
	}
	if (c == '"')
	{
		if (expand == 0)
			return (expand - 1);
		if (expand < 0)
			return (expand + 1);
	}
	return (expand);
}

static int	expand_authorize(char c)
{
	if (c == '&' || c == '|' || c == ';' || c == '/')
		return (1);
	return (0);
}

int			is_expand_tild(char *value, int index, int expand)
{
	if (index != 0)
		return (0);
	if (expand != 0)
		return (0);
	if (index - 1 < 0
		|| ft_isspace(value[index - 1]) || expand_authorize(value[index - 1]))
		if ((!value[index + 1])
			|| ft_isspace(value[index + 1])
			|| expand_authorize(value[index + 1]))
			return (1);
	return (0);
}
