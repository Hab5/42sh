/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:56:32 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 20:38:51 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_check_and_go(t_cd *cd)
{
	struct stat	sb;

	if (stat(cd->curpath, &sb) == -1)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: %s: no such file or directory\n",
				cd->directory);
		return (cd_err(cd));
	}
	if ((sb.st_mode & S_IFMT) != S_IFDIR)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: %s: not a directory\n",
				cd->directory);
		return (cd_err(cd));
	}
	if (cd_chdir(cd))
		return (cd_err(cd));
	return (0);
}

static int	cd_p_noslash_canonical(t_cd *cd)
{
	char	*bin;
	char	*binn;

	if (cd->arg_p == 1)
		return (cd_check_and_go(cd));
	if (cd->curpath[0] != '/')
	{
		if (is_env_empty("PWD"))
			bin = ft_strdup(".");
		else
			bin = value_line_path("PWD", 0);
		if (!bin)
			return (cd_err(cd));
		binn = cd->curpath;
		cd->curpath = ft_jointhree(bin, "/", cd->curpath);
		ft_strdel(&binn);
		ft_strdel(&bin);
		if (!cd->curpath)
			return (cd_err(cd));
	}
	if (!cd_canonical(cd))
		return (cd_err(cd));
	return (cd_check_and_go(cd));
}

static int	cd_testcdpath_curpath(t_cd *cd)
{
	char	*test;

	test = NULL;
	if (is_env_empty("CDPATH"))
	{
		if (!cd_testpath(".", cd->directory, &test))
			return (0);
		cd->curpath = test;
		return (1);
	}
	return (cd_test_cdpath(cd, &(*test)));
}

static int	cd_init(char **av, t_cd *cd)
{
	int		i;
	int		ac;

	cd->arg__ = 0;
	cd->arg_l = 1;
	cd->arg_p = 0;
	cd->curpath = NULL;
	ac = 1;
	while (av[ac])
		ac++;
	if (!(i = cd_getopt(ac, av, cd)) || i < ac - 1)
	{
		if (i != 0)
			ft_dprintf(STDERR_FILENO, "42sh: cd: too many arguments\n");
		return (0);
	}
	if (!av[i])
	{
		cd->directory = NULL;
		return (1);
	}
	if (ft_strequ(av[i], "-"))
		return (cd_less(cd));
	cd->directory = ft_strdup(av[i]);
	return (1);
}

int			bt_cd(char **av, t_redirection *r)
{
	t_cd	cd;

	redirection_fd(r);
	if (!cd_init(av, &cd))
		return (1);
	if (cd_dirnull(&cd))
		return (cd_err(&cd));
	if (cd.directory[0] == '/')
	{
		if ((cd.curpath = ft_strdup(cd.directory)) == NULL)
			return (cd_err(&cd));
		return (cd_p_noslash_canonical(&cd));
	}
	if (cd.directory[0] != '.' ||
		(cd.directory[0] != '.' && cd.directory[1] != '.'))
	{
		if (cd_testcdpath_curpath(&cd))
			return (cd_p_noslash_canonical(&cd));
		ft_dprintf(STDERR_FILENO, "42sh: cd: %s: No such file or directory\n",
				cd.directory);
		return (cd_err(&cd));
	}
	if ((cd.curpath = ft_strdup(cd.directory)) == NULL)
		return (cd_err(&cd));
	return (cd_p_noslash_canonical(&cd));
}
