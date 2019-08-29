/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:02:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/24 05:27:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** split :
** find arg
** apply ft avec tableau de pointeur
*/

static char		*(**init_array(void))(char*, char*)
{
	char	*(**conv)(char*, char*);
	int		i;

	conv = ft_memalloc(255 * sizeof(void*));
	i = -1;
	while (++i <= 254)
		conv[i] = 0;
	conv['-'] = &parameter_moins;
	conv['='] = &parameter_equals;
	conv['?'] = &parameter_interrogation;
	conv['+'] = &parameter_plus;
	return (conv);
}

char			*gest_expansion(char *key, char *value)
{
	char	*(**conv)(char*, char*);
	char	*final;
	char	*value_expand;

	conv = init_array();
	final = NULL;
	if (value && (int)value[0] != 0 && conv[(int)value[0]])
	{
		value_expand = search_var(value + 1);
		final = (*conv[(int)value[0]])(key, value_expand);
		ft_strdel(&value_expand);
	}
	else
		display_error_syntax(key, value);
	free(conv);
	conv = NULL;
	return (final);
}
