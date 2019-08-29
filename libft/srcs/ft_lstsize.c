/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 02:34:39 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/18 02:37:39 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_lst **head)
{
	int		count;
	t_lst	*curlist;

	curlist = *head;
	count = 0;
	while (curlist)
	{
		++count;
		curlist = curlist->next;
	}
	return (count);
}
