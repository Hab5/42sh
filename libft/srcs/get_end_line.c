/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:48:31 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 06:19:53 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int		get_end_line(char *file)
{
	int		fd;
	int		verif;
	char	*str;

	fd = open(file, O_RDWR);
	verif = 0;
	while ((verif = get_next_line(fd, &str)) > 0)
		ft_strdel(&str);
	return (fd);
}
