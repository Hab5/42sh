/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:09:25 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 08:39:37 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_ht_hash	*g_alias_table;
extern t_ht_hash	*g_hash_table;

static int			type_alias_hash(char *command)
{
	char	*val;

	if ((val = ht_hash_search(g_alias_table, command)))
	{
		ft_printf("%s is aliased to `%s'\n", command, val);
		return (1);
	}
	else if ((val = ht_hash_search(g_hash_table, command)))
	{
		ft_printf("%s is hashed (%s)\n", command, val);
		return (1);
	}
	return (0);
}

static int			type_builtin(char *command)
{
	if ((ft_strequ(command, "echo") || (ft_strequ(command, "cd"))))
		return (1);
	else if ((ft_strequ(command, "exit") || (ft_strequ(command, "jobs"))))
		return (1);
	else if ((ft_strequ(command, "fg") || (ft_strequ(command, "bg"))))
		return (1);
	else if ((ft_strequ(command, "fc") || (ft_strequ(command, "alias"))))
		return (1);
	else if ((ft_strequ(command, "unalias") || (ft_strequ(command, "hash"))))
		return (1);
	else if ((ft_strequ(command, "type") || (ft_strequ(command, "env"))))
		return (1);
	else if ((ft_strequ(command, "set") || (ft_strequ(command, "setenv"))))
		return (1);
	else if ((ft_strequ(command, "unsetenv") || (ft_strequ(command, "export"))))
		return (1);
	else if (ft_strequ(command, "unset") || (ft_strequ(command, "test")))
		return (1);
	return (0);
}

static int			bt_type_err(char **av, int i)
{
	ft_dprintf(STDERR_FILENO, "type: %s: not found\n", av[i]);
	return (1);
}

int					bt_type(char **av, t_redirection *r)
{
	int		i;
	int		ret;
	char	*arg;

	i = 1;
	ret = 0;
	redirection_fd(r);
	while (av[i])
	{
		if (type_builtin(av[i]))
			ft_printf("%s is a shell builtin\n", av[i]);
		else if (type_alias_hash(av[i]))
			;
		else if ((arg = is_in_path(av[i], 0)))
		{
			ft_printf("%s is %s\n", av[i], arg);
			ft_strdel(&arg);
		}
		else
			ret = bt_type_err(av, i);
		++i;
	}
	return (ret);
}
