/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:22:06 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 15:19:32 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		cd_test_cdpath(t_cd *cd, char *test)
{
	int		j;
	char	*path;

	if ((path = value_line_path("CDPATH", 0)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: Failed to malloc\n");
		return (0);
	}
	j = 0;
	while (path[j] != '\0')
	{
		if ((cd_testcdpath(&(path[j]), cd->directory, &test)))
		{
			cd->curpath = test;
			ft_strdel(&path);
			return (1);
		}
		j += cd_getnextpath(&(path[j]), 0);
	}
	ft_strdel(&path);
	if (!cd_testpath(".", cd->directory, &test))
		return (0);
	cd->curpath = test;
	return (1);
}

int		is_env_empty(char *value)
{
	char *str;

	str = value_line_path(value, 0);
	if (str)
	{
		if (ft_strequ(str, ""))
		{
			ft_strdel(&str);
			return (1);
		}
		else
		{
			ft_strdel(&str);
			return (0);
		}
	}
	return (1);
}

int		cd_getnextpath(char *path, int tozero)
{
	int	i;

	i = 0;
	while (path[i] != '\0' && path[i] != ':')
		i++;
	if (path[i] != '\0')
		return (i + 1 - tozero);
	return (i);
}

int		cd_testpath(char *path, char *directory, char **test)
{
	int		i;
	char	*tmp;

	i = ft_strlen(path);
	if (path[i - 1] == '/')
		tmp = ft_strjoin(path, directory);
	else
		tmp = ft_jointhree(path, "/", directory);
	if (access(tmp, F_OK) == 0)
	{
		*test = tmp;
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

/*
** Function to test a pathname of CDPATH
*/

int		cd_testcdpath(char *path, char *directory, char **test)
{
	int		i;
	int		j;
	char	*tmp;
	char	sav;

	if ((i = cd_getnextpath(path, 1)) < 2)
		return (0);
	if ((tmp = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: cd: Failed to malloc\n");
		return (0);
	}
	sav = path[i];
	path[i] = '\0';
	tmp = ft_strcpy(tmp, path);
	j = cd_testpath(tmp, directory, test);
	path[i] = sav;
	ft_strdel(&tmp);
	return (j);
}
