/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/20 03:23:48 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_ht_hash	*g_alias_table;
extern int			g_optind;

int					unalias_getopt(char **av)
{
	char	arg;
	int		ac;
	int		arg_a;
	int		i;

	ac = 0;
	arg_a = 0;
	while (av[ac])
		++ac;
	while ((arg = ft_getopt(ac, av, "a")) != -1)
	{
		if (arg == 'a')
			arg_a = 1;
		else
		{
			ft_dprintf(2, "usage: unalias [-a] [name...]\n");
			ft_getopt_reset();
			return (0);
		}
	}
	i = g_optind;
	ft_getopt_reset();
	if (arg_a)
		ht_hash_reset(&g_alias_table);
	return (i);
}

int					bt_unalias(char **av, t_redirection *r)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	redirection_fd(r);
	if (!av[1])
	{
		ft_dprintf(2, "unalias: not enough arguments\n");
		return (1);
	}
	if (!(i = unalias_getopt(av)))
		return (1);
	while (av[i])
	{
		if (ht_hash_search(g_alias_table, av[i]) != NULL)
			ht_hash_delete(g_alias_table, av[i]);
		else
		{
			ft_dprintf(2, "unalias: no such hash table element: %s\n", av[i]);
			ret = 1;
		}
		++i;
	}
	return (ret);
}
