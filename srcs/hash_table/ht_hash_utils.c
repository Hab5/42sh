/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:52:09 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 20:14:16 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_hash	g_hash_deleted;

int			ht_hash_hash(const char *s, const int a, const int m)
{
	long	hash;
	int		len;
	int		i;

	hash = 0;
	len = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		hash += ft_lpow(a, len - (i + 1)) * s[i];
		hash = hash % m;
		++i;
	}
	return ((int)hash);
}

int			ht_hash_get_hash(const char *s, const int num, const int attempt)
{
	int		hash_a;
	int		hash_b;

	hash_a = ht_hash_hash(s, HT_HASH_HASH_ONE, num);
	hash_b = ht_hash_hash(s, HT_HASH_HASH_TWO, num);
	if (hash_b == num - 1)
		--hash_b;
	return ((hash_a + (attempt * (hash_b + 1))) % num);
}

void		ht_hash_del(t_ht_hash *ht)
{
	int		i;
	t_hash	*item;

	if (!ht)
		return ;
	i = 0;
	while (i < ht->size)
	{
		item = ht->hash[i];
		if (item != NULL && item != &g_hash_deleted)
			hash_del(item);
		++i;
	}
	ft_memdel((void **)&(ht->hash));
	ft_memdel((void **)&ht);
}

t_ht_hash	*ht_hash_new_sized(const int base_size)
{
	t_ht_hash	*ht;

	if ((ht = (t_ht_hash *)malloc(sizeof(t_ht_hash))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: malloc error\n");
		return (NULL);
	}
	ht->base_size = base_size;
	ht->size = ft_nextprime(ht->base_size);
	ht->count = 0;
	if ((ht->hash = (t_hash **)malloc(sizeof(t_hash*) * ht->size)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: malloc error\n");
		ft_memdel((void**)&ht);
		return (NULL);
	}
	ht_hash_table_null(ht->hash, ht->size);
	return (ht);
}

t_ht_hash	*ht_hash_new(void)
{
	return (ht_hash_new_sized(HT_HASH_BASE_SIZE));
}
