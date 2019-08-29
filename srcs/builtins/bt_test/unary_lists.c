/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 05:37:35 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 07:40:39 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	create_more_unary(t_unary_tab **tab_lst)
{
	(*tab_lst)[8].str = ft_strdup("-r");
	(*tab_lst)[8].f = &r_test;
	(*tab_lst)[9].str = ft_strdup("-S");
	(*tab_lst)[9].f = &upper_s_test;
	(*tab_lst)[10].str = ft_strdup("-s");
	(*tab_lst)[10].f = &s_test;
	(*tab_lst)[11].str = ft_strdup("-u");
	(*tab_lst)[11].f = &u_test;
	(*tab_lst)[12].str = ft_strdup("-w");
	(*tab_lst)[12].f = &w_test;
	(*tab_lst)[13].str = ft_strdup("-x");
	(*tab_lst)[13].f = &x_test;
	(*tab_lst)[14].str = ft_strdup("-z");
	(*tab_lst)[14].f = &z_test;
	(*tab_lst)[15].str = NULL;
	(*tab_lst)[15].f = NULL;
}

void	create_unary_list(t_unary_tab **tab_lst)
{
	if (!((*tab_lst) = (t_unary_tab *)ft_memalloc(sizeof(t_unary_tab) * 16)))
		return ;
	(*tab_lst)[0].str = ft_strdup("-b");
	(*tab_lst)[0].f = &b_test;
	(*tab_lst)[1].str = ft_strdup("-c");
	(*tab_lst)[1].f = &c_test;
	(*tab_lst)[2].str = ft_strdup("-d");
	(*tab_lst)[2].f = &d_test;
	(*tab_lst)[3].str = ft_strdup("-e");
	(*tab_lst)[3].f = &e_test;
	(*tab_lst)[4].str = ft_strdup("-f");
	(*tab_lst)[4].f = &f_test;
	(*tab_lst)[5].str = ft_strdup("-g");
	(*tab_lst)[5].f = &g_test;
	(*tab_lst)[6].str = ft_strdup("-L");
	(*tab_lst)[6].f = &upper_l_test;
	(*tab_lst)[7].str = ft_strdup("-p");
	(*tab_lst)[7].f = &p_test;
	create_more_unary(tab_lst);
}

void	create_binary_list(t_unary_tab **tab_lst)
{
	if (!((*tab_lst) = (t_unary_tab *)ft_memalloc(sizeof(t_unary_tab) * 8)))
		return ;
	(*tab_lst)[0].str = ft_strdup("=");
	(*tab_lst)[0].f = &equal_test;
	(*tab_lst)[1].str = ft_strdup("!=");
	(*tab_lst)[1].f = &notequal_test;
	(*tab_lst)[2].str = ft_strdup("-eq");
	(*tab_lst)[2].f = &eq_test;
	(*tab_lst)[3].str = ft_strdup("-ne");
	(*tab_lst)[3].f = &ne_test;
	(*tab_lst)[4].str = ft_strdup("-ge");
	(*tab_lst)[4].f = &ge_test;
	(*tab_lst)[5].str = ft_strdup("-lt");
	(*tab_lst)[5].f = &lt_test;
	(*tab_lst)[6].str = ft_strdup("-le");
	(*tab_lst)[6].f = &le_test;
	(*tab_lst)[7].str = NULL;
	(*tab_lst)[7].f = NULL;
}

void	clean_test_tab(t_unary_tab **tab_lst)
{
	int		i;

	i = 0;
	while ((*tab_lst)[i].str)
	{
		ft_strdel(&((*tab_lst)[i].str));
		i++;
	}
	ft_memdel((void**)tab_lst);
}
