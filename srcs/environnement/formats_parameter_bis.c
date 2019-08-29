/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_parameter_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:12:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 11:33:34 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** return parameter si existe sinon word
*/

char	*parameter_moins(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (!src)
		src = ft_strdup(word);
	return (src);
}

/*
** si parameter non initialiser alors donner valeur word et return
** valeur de parameter
*/

char	*parameter_equals(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (!src)
	{
		add_set_value(parameter, word);
		src = ft_strdup(word);
	}
	return (src);
}

/*
** si parameter est initialise return sinon parameter a null et
** affiche message d’erreur
*/

char	*parameter_interrogation(char *parameter, char *word)
{
	char	*src;
	char	*error;

	src = value_line_path(parameter, 0);
	if (!word || ft_strequ(word, ""))
		error = ft_strdup("parameter null or not set");
	else
		error = ft_strdup(word);
	if (!src)
	{
		display_other_error(STDERR_FILENO, parameter, error);
		gest_return(-5);
		src = NULL;
	}
	ft_strdel(&error);
	return (src);
}

/*
** si parameter existe et a deja une valeur,
** remplace ca valeur par word
*/

char	*parameter_plus(char *parameter, char *word)
{
	char	*src;

	src = value_line_path(parameter, 0);
	if (src && ft_strequ(src, "") == 0)
	{
		ft_strdel(&src);
		add_set_value(parameter, word);
		src = ft_strdup(word);
	}
	return (src);
}
