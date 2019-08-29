/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash_stillutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:50:42 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 20:09:05 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void				ht_hash_reset(t_ht_hash **ht)
{
	if (!ht)
		return ;
	ht_hash_del(*ht);
	*ht = ht_hash_new();
}

void				ht_hash_table_null(t_hash **hash, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		hash[i] = NULL;
		++i;
	}
}

void				ht_hash_resize_up(t_ht_hash *ht)
{
	int	new_size;

	new_size = ht->base_size * 2;
	ht_hash_resize(ht, new_size);
}

void				ht_hash_resize_down(t_ht_hash *ht)
{
	int	new_size;

	new_size = ht->base_size / 2;
	ht_hash_resize(ht, new_size);
}
