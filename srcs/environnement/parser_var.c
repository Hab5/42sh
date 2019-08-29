/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 20:32:54 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** Remplace les variables.
** Args:	char *value -> la commande de base
**			char **dst -> la commande avec les modifications
**			int *i -> adresse de l'index actuel de value
**			int last -> adresse de l'index value de la derniere modification
*/

int			apply_parser_var(char *value, char **dst, int *i, int last)
{
	if ((*i) != last)
		copy_value(value, dst, last, (*i));
	if (value[(*i)] == '~')
		(*i) = manage_home(value, dst, (*i)) - 1;
	else if (value[(*i)] == '$')
		(*i) = apply_rules(value, dst, (*i));
	return ((*i) + 1);
}

int			count_slash(char *line, int i)
{
	int	j;
	int	cnt;
	int	expand;

	j = -1;
	cnt = 0;
	expand = 0;
	while (--i >= 0 && line[i] && line[i] == '\\')
	{
		++cnt;
	}
	cnt %= 2;
	return (cnt);
}

/*
** Parcours un char* pour chercher les valeurs a remplacer
** Args:	char **value -> adresse d'un char*
*/

void		parser_var_simple(char **value, uint8_t flag)
{
	int		i;
	int		expand;
	int		len;
	int		last;
	char	*dst;

	i = -1;
	last = 0;
	expand = 0;
	len = ft_strlen(*value);
	dst = ft_strdup("");
	while (++i < len)
	{
		expand = flag == 0 ? 0 : manage_is_quote((*value), i, expand);
		if (expand <= 0 && (i - 1 < 0 || (!count_slash((*value), i)))
			&& ((*value)[i] == '$'
			|| ((*value)[i] == '~' && is_expand_tild(*value, i, expand))))
			last = apply_parser_var(*value, &dst, &i, last);
	}
	if (i != last)
		copy_value(*value, &dst, last, i);
	ft_strdel(value);
	*value = dst;
	if (flag == 1)
		remove_quote_line(value);
}

/*
** Gestion des variables. Parcours un tableaux de char* et envoie chaque ligne
** dans la fonction parser_var_simple.
** Args:	char ***value -> adresse d'un tableau de char*
*/

void		parser_var(char ***value)
{
	int		i;

	i = -1;
	if ((!value) || (!*value))
		return ;
	while ((*value)[++i])
		parser_var_simple(&((*value)[i]), 1);
}
