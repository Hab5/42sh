/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <aleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:13:47 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/08 16:14:30 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstprinthead(t_dlist **head)
{
	t_dlist	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl((char *)ptr->data);
		ptr = ptr->next;
	}
}

void	ft_dlstprinttail(t_dlist **tail)
{
	t_dlist	*ptr;

	ptr = *tail;
	while (ptr->prev)
	{
		ft_putendl((char *)ptr->data);
		ptr = ptr->prev;
	}
}

int		ft_dlstiter(t_dlist **head)
{
	t_dlist	*ptr;
	int		count;

	count = 0;
	ptr = *head;
	while (ptr)
	{
		++count;
		ptr = ptr->next;
	}
	return (count);
}
