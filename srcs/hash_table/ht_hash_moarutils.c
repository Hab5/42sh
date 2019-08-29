/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash_moarutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:58:23 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 21:14:26 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_hash	g_hash_deleted;

void			ht_hash_delete_item(t_ht_hash *ht, const char *key,
									t_hash *item, int index)
{
	if (item != &g_hash_deleted)
	{
		if (ft_strcmp(item->key, key) == 0)
		{
			hash_del(item);
			ht->hash[index] = &g_hash_deleted;
		}
	}
}

void			ht_hash_insert_item(t_ht_hash *ht, const char *key,
									t_hash *item, int index)
{
	int		i;
	t_hash	*cur_item;

	cur_item = ht->hash[index];
	i = 1;
	while (cur_item != NULL)
	{
		if (cur_item != &g_hash_deleted)
		{
			if (ft_strcmp(cur_item->key, key) == 0)
			{
				hash_del(cur_item);
				ht->hash[index] = item;
				return ;
			}
		}
		index = ht_hash_get_hash(key, ht->size, i);
		cur_item = ht->hash[index];
		++i;
	}
	ht->hash[index] = item;
	++ht->count;
}
