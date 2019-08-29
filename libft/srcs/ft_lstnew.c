/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:57:38 by aleduc            #+#    #+#             */
/*   Updated: 2018/06/07 14:46:22 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*init;

	if (!(init = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	init->content = ft_memalloc(content_size);
	if (!content)
	{
		init->content = NULL;
		init->content_size = 0;
	}
	else
	{
		ft_memcpy(init->content, content, content_size);
		init->content_size = content_size;
	}
	init->next = NULL;
	return (init);
}
