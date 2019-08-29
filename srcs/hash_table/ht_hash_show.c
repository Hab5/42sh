/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash_show.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:19:19 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/26 01:11:45 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_hash				g_hash_deleted;

static void					ht_tree_del(t_hash_tree *tree)
{
	if (tree == NULL)
		return ;
	ht_tree_del(tree->left);
	tree->left = NULL;
	ht_tree_del(tree->right);
	tree->right = NULL;
	tree->hash = NULL;
	free(tree);
}

static void					ht_tree_show(t_hash_tree *tree, int quote)
{
	if (tree == NULL)
		return ;
	ht_tree_show(tree->left, quote);
	if (quote == 1)
		ft_printf("%s='%s'\n", tree->hash->key, tree->hash->value);
	else
		ft_printf("%s=%s\n", tree->hash->key, tree->hash->value);
	ht_tree_show(tree->right, quote);
}

static t_hash_tree			*tree_create(t_hash *hash)
{
	t_hash_tree	*branch;

	if ((branch = (t_hash_tree *)malloc(sizeof(t_hash_tree))) == NULL)
		return (NULL);
	branch->hash = hash;
	branch->left = NULL;
	branch->right = NULL;
	return (branch);
}

static t_hash_tree			*ht_tree_add(t_hash *hash, t_hash_tree *tree)
{
	int	res;

	if (tree == NULL)
		return (tree_create(hash));
	res = ft_strcmp(hash->key, tree->hash->key);
	if (res <= 0)
	{
		if (tree->left == NULL)
		{
			tree->left = tree_create(hash);
			return (tree);
		}
		tree->left = ht_tree_add(hash, tree->left);
		return (tree);
	}
	else
	{
		if (tree->right == NULL)
		{
			tree->right = tree_create(hash);
			return (tree);
		}
		tree->right = ht_tree_add(hash, tree->right);
		return (tree);
	}
}

void						ht_hash_show(t_ht_hash *ht, int quote)
{
	t_hash_tree	*tree;
	int			i;

	if (!ht)
		return ;
	i = 0;
	tree = NULL;
	while (i < ht->size)
	{
		if (ht->hash[i] && ht->hash[i] != &g_hash_deleted)
			tree = ht_tree_add(ht->hash[i], tree);
		++i;
	}
	ht_tree_show(tree, quote);
	ht_tree_del(tree);
	tree = NULL;
}
