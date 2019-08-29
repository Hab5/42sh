/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttail.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:45:19 by aleduc            #+#    #+#             */
/*   Updated: 2018/08/25 12:28:47 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lsttail(t_list **alst, t_list *node)
{
	t_list	*curlist;

	curlist = *alst;
	while (curlist->next)
		curlist = curlist->next;
	curlist->next = node;
}
