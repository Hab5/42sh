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

t_dlist	*ft_dlstnew(void *data, size_t data_size)
{
	t_dlist	*node;

	if (!(node = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	node->data = ft_memalloc(data_size);
	if (!data)
	{
		node->data = NULL;
		node->data_size = 0;
	}
	else
	{
		ft_memcpy(node->data, data, data_size);
		node->data_size = data_size;
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
