/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:23:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 20:13:48 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		delete_redirection(t_redirection **r)
{
	t_redirect	*next;

	next = NULL;
	if ((!r) || (!(*r)))
		return ;
	while ((*r)->redirect)
	{
		next = ((*r)->redirect->next) ? (*r)->redirect->next : NULL;
		if ((*r)->redirect->new_fd != -1
				&& verif_close((*r)->redirect->new_fd))
			close((*r)->redirect->new_fd);
		ft_strdel(&((*r)->redirect->name_file));
		free((*r)->redirect);
		(*r)->redirect = NULL;
		(*r)->redirect = next;
	}
	free(*r);
	(*r) = NULL;
}

static int	test_verif_close(char *str, int fd, int verif)
{
	int	fd_sys;

	if (str)
	{
		fd_sys = ft_atoi(str);
		if (fd == fd_sys)
			verif = 0;
	}
	return (verif);
}

int			verif_close(int fd)
{
	int		verif;
	char	*in;
	char	*out;
	char	*error;

	verif = 1;
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO
		|| (fd > -1 && fd < 3))
		return (0);
	in = value_line_path("STDIN", 3);
	out = value_line_path("STDOUT", 3);
	error = value_line_path("STDERR", 3);
	verif = test_verif_close(in, fd, verif);
	verif = test_verif_close(out, fd, verif);
	verif = test_verif_close(error, fd, verif);
	ft_strdel(&in);
	ft_strdel(&out);
	ft_strdel(&error);
	return (verif);
}
