/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:11:36 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

int			edit_export(char *key)
{
	int		verif;
	t_env	*head;
	t_env	*my_env;

	my_env = get_env(0, NULL);
	head = my_env;
	verif = 0;
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			verif = 1;
			my_env->see_env = 1;
			break ;
		}
		my_env = my_env->next;
	}
	my_env = head;
	return (verif);
}
