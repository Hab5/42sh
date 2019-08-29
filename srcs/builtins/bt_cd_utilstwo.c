/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utilstwo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:27:24 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 20:39:19 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern	int g_optind;

int		cd_err(t_cd *cd)
{
	if (cd->directory)
		ft_strdel(&cd->directory);
	if (cd->curpath)
		ft_strdel(&cd->curpath);
	return (1);
}

int		cd_chdir(t_cd *cd)
{
	char	*tmp;
	char	*bin;

	if (chdir(cd->curpath) == -1)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: %s: permission denied\n",
				cd->directory);
		return (cd_err(cd));
	}
	tmp = value_line_path("PWD", 0);
	if (cd->arg_p)
	{
		bin = getcwd(NULL, MAXPATHLEN);
		edit_setenv("PWD", bin);
		ft_strdel(&bin);
	}
	else
		edit_setenv("PWD", cd->curpath);
	edit_setenv("OLDPWD", tmp);
	if (cd->arg__)
		ft_printf("%s\n", cd->curpath);
	ft_strdel(&tmp);
	ft_strdel(&cd->directory);
	ft_strdel(&cd->curpath);
	return (0);
}

int		cd_canonical_del(t_cd *cd, size_t a, size_t b, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if ((tmp = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	tmp[len] = '\0';
	i = 0;
	j = 0;
	while (cd->curpath[i] != '\0' && j < len)
	{
		if (i == a && a != b)
			i = b;
		tmp[j] = cd->curpath[i];
		if (cd->curpath[i] != '\0')
			i++;
		j++;
	}
	tmp[len] = '\0';
	ft_strdel(&(cd->curpath));
	cd->curpath = tmp;
	return (1);
}

/*
** 8 - curpath shall be converted to canonical form as follows :
**         a. dot components and any '/' that separate them from the next
**				component shall be deleted
**         b. For each '..', if there is a preceding component and it is
**					neither root nor '..', then :
**             i. If preceding component does not refer directory
**					(ex. symbolic link), display error message and stop
**             ii. Preceding component, '/', '..' and '/' (if any) shall be
**					deleted
**         c. An implementation ma further simplify curpath b removing any
**					trailng '/' that are not also leading '/',
**            		replacing multiple consecutive '/' by a single '/',
**					and replacing three or more leading '/' by a single '/'
**     If after step 8, curpath is null, stop
*/

int		cd_canonical(t_cd *cd)
{
	if (cd_canonical_a(cd))
		return (0);
	if (cd_canonical_b(cd))
		return (0);
	cd_canonical_c(cd);
	if (!cd->curpath || cd->curpath[0] == '\0')
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: cd: path after canonicalization is null\n");
		return (0);
	}
	return (1);
}

int		cd_getopt(char ac, char **av, t_cd *cd)
{
	int		i;
	char	arg;

	while ((arg = ft_getopt(ac, av, "LP")) != -1)
	{
		if (arg == 'L')
		{
			cd->arg_l = 1;
			cd->arg_p = 0;
		}
		else if (arg == 'P')
		{
			cd->arg_p = 1;
			cd->arg_l = 0;
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "usage: cd [-L|-P] [dir]\n");
			ft_getopt_reset();
			return (0);
		}
	}
	i = g_optind;
	ft_getopt_reset();
	return (i);
}
