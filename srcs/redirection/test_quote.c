/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/08 08:30:32 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** F_OK: file exist
*/

static void	close_file_test_quote(int fd)
{
	if (verif_close(fd))
		close(fd);
}

int			test_quote(char *name)
{
	int		fd;
	int		len;
	char	*dst;

	dst = NULL;
	len = ft_strlen(name) - 1;
	if (name[0] == '"' || name[0] == '\'')
		if (name[len] == '"' || name[len] == '\'')
			dst = ft_strsub(name, 1, len - 1);
	if (!dst)
		return (-1);
	if (access(dst, F_OK) != -1)
	{
		ft_strdel(&dst);
		return (0);
	}
	fd = open(dst, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_strdel(&dst);
	if (fd != -1)
	{
		close_file_test_quote(fd);
		return (1);
	}
	return (-1);
}
