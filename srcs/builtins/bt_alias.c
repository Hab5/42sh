/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:00:16 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 19:14:22 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int			g_optind;
extern t_ht_hash	*g_alias_table;

int					alias_getopt(char **av)
{
	char	arg;
	int		ac;
	int		i;

	ac = 0;
	while (av[ac])
		++ac;
	while ((arg = ft_getopt(ac, av, "")) != -1)
	{
		ft_dprintf(2, "usage: alias [name...]\n");
		ft_getopt_reset();
		return (0);
	}
	i = g_optind;
	ft_getopt_reset();
	return (i);
}

static int			bt_showalias(char **av, int i, int ret)
{
	char	*val;

	val = ht_hash_search(g_alias_table, av[i]);
	if (val == NULL)
	{
		ft_dprintf(2, "alias: \"%s\" : not found\n", av[i]);
		return (1);
	}
	ft_printf("%s=%s\n", av[i], val);
	return (ret);
}

static int			alias_isvalid(char *alias)
{
	int		i;

	i = 0;
	while (alias[i])
	{
		if (ft_isalnum(alias[i]))
			++i;
		else if (alias[i] == '_' || alias[i] == '!' || alias[i] == '%' ||
				alias[i] == ',' || alias[i] == '@' || alias[i] == '.' ||
				alias[i] == '#' || alias[i] == '*' || alias[i] == '+' ||
				alias[i] == '-' || alias[i] == ':' || alias[i] == '?' ||
				alias[i] == '[' || alias[i] == ']' || alias[i] == '^' ||
				alias[i] == '~')
			++i;
		else
			return (0);
	}
	return (1);
}

static int			bt_addalias(char **av, int i, int ret)
{
	char	*tmp;

	tmp = ft_strchr(av[i], '=');
	*tmp = '\0';
	if (alias_isvalid(av[i]))
		ht_hash_insert(g_alias_table, av[i], &(tmp[1]));
	else
	{
		ft_dprintf(2, "alias: \"%s\" : alias name not valid\n", av[i]);
		ret = 1;
	}
	*tmp = '=';
	return (ret);
}

int					bt_alias(char **av, t_redirection *r)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	redirection_fd(r);
	if (!av[1])
		ht_hash_show(g_alias_table, 1);
	if (!(i = alias_getopt(av)))
		return (1);
	while (av[i])
	{
		if (ft_strchr_exist(av[i], '=') && av[i][0] != '=')
			ret = bt_addalias(av, i, ret);
		else
			ret = bt_showalias(av, i, ret);
		++i;
	}
	return (ret);
}
