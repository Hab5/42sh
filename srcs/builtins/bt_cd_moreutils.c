/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_moreutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 04:11:47 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 10:11:21 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			cd_less(t_cd *cd)
{
	if (is_env_empty("OLDPWD"))
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: OLDPWD null or not set\n");
		return (0);
	}
	cd->directory = value_line_path("OLDPWD", 0);
	if (!cd->directory)
		return (0);
	cd->arg__ = 1;
	return (1);
}

int			cd_dirnull(t_cd *cd)
{
	if (cd->directory == NULL && is_env_empty("HOME"))
		return (1);
	if (cd->directory == NULL)
		cd->directory = value_line_path("HOME", 0);
	if (!cd->directory)
		return (1);
	return (0);
}
