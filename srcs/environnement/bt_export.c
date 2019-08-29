/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 19:51:58 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

static int	add_value_export(char **value, int i, int verif)
{
	char	**spl;

	if (ft_strchr_exist(value[i], '='))
	{
		spl = ft_strsplit(value[i], '=');
		if (spl && spl[0])
		{
			if (verif_syntax_key(spl[0]))
				verif = (edit_setenv(spl[0], spl[1]) == -1) ? 1 : 0;
			else
				verif = 1;
		}
		ft_arraydel(&spl);
	}
	else
		verif = (edit_export(value[i]) == 1) ? 0 : 1;
	return (verif);
}

int			bt_export(char **value, t_redirection *r)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	if (!value[1])
	{
		builtin_env_display(r);
		return (0);
	}
	while (value[++i])
		verif = add_value_export(value, i, verif);
	return (verif);
}
