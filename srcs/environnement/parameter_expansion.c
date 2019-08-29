/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:02:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/24 05:12:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int				search_good_expansion(char *tmp)
{
	int	i;

	i = -1;
	if (tmp[0] == '#')
		return (1);
	while (tmp[++i])
	{
		if (tmp[i] == '#')
			return (2);
		else if (tmp[i] == '%')
			return (3);
		else if (tmp[i] == ':')
			return (4);
	}
	return (0);
}

int				is_other_expansion(char *tmp, char **dst)
{
	int		expansion;
	char	*stock;
	char	*stock_b;

	expansion = search_good_expansion(tmp);
	if (expansion == 1)
		stock = parameter_hash_first(tmp + 1);
	else if (expansion == 2)
		stock = parameter_hash_end(tmp);
	else if (expansion == 3)
		stock = parameter_percents(tmp);
	else
		return (check_format_variable(tmp) ? 0 : -1);
	if (stock)
	{
		stock_b = ft_strjoin(*dst, stock);
		ft_strdel(dst);
		ft_strdel(&stock);
		*dst = stock_b;
	}
	return (1);
}

void			manage_parameter_extension(char **dst, char *tmp, int i)
{
	char	*key;
	char	*tmp_b;

	key = ft_strsub(tmp, 0, i);
	if ((!key) || ft_strequ(key, "")
		|| (ft_isalnum(key[0]) == 0 && key[0] != '#'))
	{
		ft_strdel(&key);
		display_error_expansion(tmp);
		return ;
	}
	tmp_b = gest_expansion(key, tmp + i + 1);
	ft_strdel(&key);
	key = ft_strjoin(*dst, tmp_b);
	ft_strdel(dst);
	ft_strdel(&tmp_b);
	(*dst) = key;
}

void			parameter_expansion(char *tmp, char **dst)
{
	int		expansion;
	int		verif;
	int		i;

	if ((!tmp) || ft_strequ(tmp, ""))
	{
		display_error_expansion("");
		return ;
	}
	i = ft_chr_index(tmp, ':');
	expansion = search_good_expansion(tmp);
	if (expansion != 4)
	{
		if ((verif = is_other_expansion(tmp, dst)) == 0)
			modify_dst(tmp, dst);
		else if (verif == -1)
			display_error_expansion(tmp);
	}
	else if (expansion != -1)
		manage_parameter_extension(dst, tmp, i);
}
