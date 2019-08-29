/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary_primaries.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 00:46:12 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 07:51:58 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		s_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_size > 0)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		u_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if ((sb.st_mode & S_IFMT) == S_ISUID)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		w_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IWUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		x_test(char *str1, char *str2, char *str3)
{
	struct stat	sb;

	if (stat(str2, &sb) != -1)
	{
		if (sb.st_mode & S_IXUSR)
			return (0);
	}
	(void)str1;
	(void)str3;
	return (1);
}

int		z_test(char *str1, char *str2, char *str3)
{
	if (ft_strlen(str2) == 0)
		return (0);
	(void)str1;
	(void)str3;
	return (1);
}
