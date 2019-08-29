/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:31:02 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/05 02:43:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		modify_dst(char *src, char **dst)
{
	char	*stock;
	char	*final;

	if (!src || src[0] == 0)
		final = ft_strjoin(*dst, "$");
	else
	{
		stock = manage_var(src);
		final = ft_strjoin(*dst, stock);
		ft_strdel(&stock);
	}
	if (final)
	{
		ft_strdel(dst);
		(*dst) = final;
	}
	return (0);
}

char	*manage_var(char *str)
{
	char	*final;

	if (ft_strequ(str, "$"))
		final = ft_itoa(getpid());
	else
		final = value_line_path(str, 0);
	if (!final)
		final = ft_strdup("");
	return (final);
}

int		manage_home(char *src, char **dst, int index)
{
	char	*tmp;
	char	*data;

	index += 1;
	if (src[index] == '-')
	{
		index++;
		data = manage_var("OLDPWD");
	}
	else if (src[index] == '+')
	{
		index++;
		data = manage_var("PWD");
	}
	else
		data = manage_var("HOME");
	tmp = ft_strjoin(*dst, data);
	ft_strdel(dst);
	ft_strdel(&data);
	(*dst) = tmp;
	return (index);
}
