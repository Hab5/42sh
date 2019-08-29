/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_unary_primaries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 07:50:45 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 07:50:57 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		b_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFBLK)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		c_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFCHR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		d_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		e_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
		return (0);
	(void)str1;
	(void)str3;
	return (1);
}

int		f_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_IFREG)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}
