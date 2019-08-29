/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_canonical_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:47:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 13:48:59 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		cd_canonical_getdot(t_cd *cd, size_t *a, size_t *b)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (cd->curpath[i] != '\0')
	{
		if (cd->curpath[i] == '.' && i != 0)
		{
			if (cd->curpath[i + j] == '/' || cd->curpath[i + j] == '\0')
			{
				while (cd->curpath[i + j] == '/')
					j++;
				*a = i;
				*b = i + j;
				return (1);
			}
		}
		while (cd->curpath[i] != '\0' && cd->curpath[i] != '/')
			i++;
		if (cd->curpath[i] != '\0')
			i++;
	}
	return (0);
}

/*
** a. dot components and any '/' that separate them from the next component
**	  shall be deleted
*/

int				cd_canonical_a(t_cd *cd)
{
	size_t	a;
	size_t	b;
	size_t	len;

	a = 0;
	b = 0;
	while (cd_canonical_getdot(cd, &a, &b))
	{
		len = ft_strlen(cd->curpath);
		len -= b - a;
		if (!cd_canonical_del(cd, a, b, len))
		{
			ft_dprintf(STDERR_FILENO, "42sh: cd: error malloc\n");
			return (1);
		}
	}
	return (0);
}
