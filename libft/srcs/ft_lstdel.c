/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:47:28 by aleduc            #+#    #+#             */
/*   Updated: 2017/11/22 13:23:18 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*curlist;

	curlist = *alst;
	while (curlist->next != NULL)
	{
		del(curlist->content, curlist->content_size);
		free(curlist);
		curlist = curlist->next;
	}
	del(curlist->content, curlist->content_size);
	free(curlist);
	*alst = NULL;
}
