/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_primaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 23:33:48 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 15:23:37 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		eq_test(char *str1, char *str2, char *str3)
{
	int		int1;
	int		int3;

	if (verify_only_alpha(str1, str3))
	{
		ft_putendl_fd("42sh: test: integer expression expected", STDERR_FILENO);
		return (30);
	}
	int1 = ft_atoi(str1);
	int3 = ft_atoi(str3);
	if (int1 == int3)
		return (0);
	(void)str2;
	return (1);
}

int		ne_test(char *str1, char *str2, char *str3)
{
	int		int1;
	int		int3;

	if (verify_only_alpha(str1, str3))
	{
		ft_putendl_fd("42sh: test: integer expression expected", STDERR_FILENO);
		return (30);
	}
	int1 = ft_atoi(str1);
	int3 = ft_atoi(str3);
	if (int1 == int3)
		return (1);
	(void)str2;
	return (0);
}

int		ge_test(char *str1, char *str2, char *str3)
{
	int		int1;
	int		int3;

	if (verify_only_alpha(str1, str3))
	{
		ft_putendl_fd("42sh: test: integer expression expected", STDERR_FILENO);
		return (30);
	}
	int1 = ft_atoi(str1);
	int3 = ft_atoi(str3);
	if (int1 >= int3)
		return (0);
	(void)str2;
	return (1);
}

int		lt_test(char *str1, char *str2, char *str3)
{
	int		int1;
	int		int3;

	if (verify_only_alpha(str1, str3))
	{
		ft_putendl_fd("42sh: test: integer expression expected", STDERR_FILENO);
		return (30);
	}
	int1 = ft_atoi(str1);
	int3 = ft_atoi(str3);
	if (int1 < int3)
		return (0);
	(void)str2;
	return (1);
}

int		le_test(char *str1, char *str2, char *str3)
{
	int		int1;
	int		int3;

	if (verify_only_alpha(str1, str3))
	{
		ft_putendl_fd("42sh: test: integer expression expected", STDERR_FILENO);
		return (30);
	}
	int1 = ft_atoi(str1);
	int3 = ft_atoi(str3);
	if (int1 <= int3)
		return (0);
	(void)str2;
	return (1);
}
