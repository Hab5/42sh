/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_unary_primaries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 07:51:34 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 07:51:54 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		g_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_ISGID)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		upper_l_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (lstat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFLNK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		p_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFIFO)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		r_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IRUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		upper_s_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFSOCK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}
