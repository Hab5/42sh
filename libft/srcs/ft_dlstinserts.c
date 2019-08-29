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

void	ft_dlstinsfront(t_dlist **head, t_dlist **node)
{
	(*node)->next = (*head);
	(*node)->prev = NULL;
	(*head)->prev = (*node);
	(*head) = (*node);
}

void	ft_dlstinsback(t_dlist **tail, t_dlist **node)
{
	(*node)->next = NULL;
	(*node)->prev = (*tail);
	(*tail)->next = (*node);
	(*tail) = (*node);
}

void	ft_dlstinsafter(t_dlist **prev_node, t_dlist **node)
{
	(*node)->next = (*prev_node)->next;
	(*node)->prev = (*prev_node);
	(*prev_node)->next = (*node);
	(*node)->next->prev = (*node);
}

void	ft_dlstinsbefore(t_dlist **next_node, t_dlist **node)
{
	(*node)->next = (*next_node);
	(*node)->prev = (*next_node)->prev;
	(*next_node)->prev = (*node);
	(*node)->prev->next = (*node);
}
