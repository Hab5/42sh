/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace_moreutils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:40:05 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/26 04:04:54 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		hist_rep_savenew(int start, int i, t_hist_rep *new, char *input)
{
	int		j;

	j = 0;
	while (start < i)
	{
		new->base[j] = input[start];
		++j;
		++start;
	}
	new->base[j] = '\0';
}

char		*hist_rep_rep(char *bin, char *value)
{
	char	*new;

	new = ft_strjoin(bin, value);
	ft_strdel(&bin);
	return (new);
}

char		*hist_rep_reperr(char *new, t_hist_rep *curr)
{
	ft_strdel(&new);
	ft_dprintf(2, "42sh: %s: event not found\n", curr->base);
	gest_return(1);
	return (NULL);
}

t_hist_rep	*history_replace_get(char *input, t_hist_rep *replace, int i,
								int start)
{
	int		expand;

	expand = 0;
	while (input[i])
	{
		expand = manage_is_quote(input, i, expand);
		if (input[i] == '!' && hist_rep_isvalid(&(input[i])) && expand == 0
			&& !(hist_rep_isbslashed(input, i - 1, expand)))
		{
			replace = hist_rep_save(input, start, i, replace);
			start = i;
			i += hist_rep_getexp(&(input[start]));
			replace = hist_rep_saveexp(input, start, i, replace);
			start = i;
		}
		else if (!input[i + 1] && replace != NULL)
		{
			replace = hist_rep_save(input, start, i + 1, replace);
			++i;
			start = i;
		}
		else
			++i;
	}
	return (replace);
}
