/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:43:51 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/03 12:23:33 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		(**init_array(void))(t_printf**)
{
	void			(**conv)(t_printf**);
	int				i;

	conv = ft_memalloc(255 * sizeof(void*));
	i = -1;
	while (++i <= 254)
		conv[i] = 0;
	conv['s'] = &ft_arg_s;
	conv['S'] = &ft_arg_array_s;
	conv['i'] = &ft_arg_d;
	conv['d'] = &ft_arg_d;
	conv['c'] = &ft_arg_c;
	conv['x'] = &ft_arg_x;
	conv['o'] = &ft_arg_o;
	conv['%'] = &ft_arg_percent;
	conv['u'] = &ft_arg_u;
	conv['p'] = &ft_arg_pointer;
	conv['f'] = &ft_arg_float;
	return (conv);
}

void			ft_gest_flag(t_printf **lst)
{
	void	(**conv)(t_printf**);
	int		flag;

	conv = init_array();
	flag = (int)ft_tolower(((*lst)->flag));
	if (conv[flag])
		(*conv[flag])((&(*lst)));
	free(conv);
	conv = NULL;
}
