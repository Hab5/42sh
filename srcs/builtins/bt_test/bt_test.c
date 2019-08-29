/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:04:50 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 15:20:17 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		unary_test(char *str1, char *str2)
{
	int			i;
	int			ret;
	t_unary_tab	*u_tab;

	i = 0;
	ret = 1;
	u_tab = NULL;
	create_unary_list(&u_tab);
	while (u_tab[i].f)
	{
		if (ft_strcmp(str1, u_tab[i].str) == 0)
		{
			ret = u_tab[i].f(str1, str2, str1);
			clean_test_tab(&u_tab);
			return (ret);
		}
		i++;
	}
	clean_test_tab(&u_tab);
	return (30);
}

int		binary_test(char *str1, char *str2, char *str3)
{
	int			i;
	int			ret;
	t_unary_tab	*b_tab;

	i = 0;
	ret = 1;
	b_tab = NULL;
	create_binary_list(&b_tab);
	while (b_tab[i].f)
	{
		if (ft_strcmp(str2, b_tab[i].str) == 0)
		{
			ret = b_tab[i].f(str1, str2, str3);
			clean_test_tab(&b_tab);
			return (ret);
		}
		i++;
	}
	clean_test_tab(&b_tab);
	return (30);
}

int		is_binary(char *str2)
{
	if (ft_strcmp(str2, "=") == 0)
		return (1);
	if (ft_strcmp(str2, "!=") == 0)
		return (1);
	if (ft_strcmp(str2, "-eq") == 0)
		return (1);
	if (ft_strcmp(str2, "-ne") == 0)
		return (1);
	if (ft_strcmp(str2, "-ge") == 0)
		return (1);
	if (ft_strcmp(str2, "-lt") == 0)
		return (1);
	if (ft_strcmp(str2, "-le") == 0)
		return (1);
	if (ft_strcmp(str2, "=") == 0)
		return (1);
	return (0);
}

int		bt_test(char **av, t_redirection *r)
{
	int	ac;

	ac = 0;
	redirection_fd(r);
	while (av[ac])
		ac++;
	if (ac == 1)
		return (1);
	if (ac == 2)
		return (bt_1(av[1]));
	if (ac == 3)
		return (bt_2(av[1], av[2]));
	if (ac == 4)
		return (bt_3(av[1], av[2], av[3]));
	if (ac == 5)
		return (bt_4(av[1], av[2], av[3], av[4]));
	if (ac > 6)
		return (bt_5());
	return (0);
}
