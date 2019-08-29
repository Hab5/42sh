/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstelemat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 08:45:59 by skuppers          #+#    #+#             */
/*   Updated: 2018/11/09 19:00:48 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_element_at(t_list *list, unsigned int index)
{
	t_list			*current;
	unsigned int	i;

	if (!list)
		return (NULL);
	i = 1;
	current = list;
	while (current != NULL && i <= index)
	{
		if (i == index)
			return (current);
		current = current->next;
		++i;
	}
	return (NULL);
}
