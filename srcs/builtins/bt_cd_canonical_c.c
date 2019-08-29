/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_canonical_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:20:14 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 10:11:01 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		cd_canonical_getslashbis(t_cd *cd, size_t i)
{
	if (cd->curpath[i] != '\0')
		i++;
	while (cd->curpath[i] != '\0' && cd->curpath[i] != '/')
		i++;
	return (i);
}

static int		cd_canonical_getslash(t_cd *cd, size_t *a, size_t *b)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (cd->curpath[i] != '\0')
	{
		if (cd->curpath[i] == '/')
		{
			if (cd->curpath[i + j] == '/' || (cd->curpath[i + j] == '\0'
				&& i != 0))
			{
				while (cd->curpath[i + j] == '/')
					j++;
				if (i == 0)
					j--;
				*a = i;
				*b = i + j;
				return (1);
			}
		}
		i = cd_canonical_getslashbis(cd, i);
	}
	return (0);
}

/*
** c. An implementation ma further simplify curpath b removing any trailng '/'
**		that are not also leading '/', replacing multiple consecutive '/' by
**		a single '/', and replacing three or more leading '/' by a single '/'
*/

int				cd_canonical_c(t_cd *cd)
{
	size_t	a;
	size_t	b;
	size_t	len;

	a = 0;
	b = 0;
	while (cd_canonical_getslash(cd, &a, &b))
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
