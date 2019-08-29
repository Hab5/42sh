/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:44:29 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 19:14:14 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <sys/resource.h>

/*
** pos -> pour les heredocs
** LESS -> <
** DLESS -> <<
** GREAT -> >
** DGREAT -> >>
** AMPGREAT -> &>
** GREATAMP -> >&
** LESSAMP -> <&
*/

int			verif_file_descriptor(char **src, char *dst)
{
	int				i;
	struct rlimit	lim;
	uintmax_t		lim_cur;

	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		return (-1);
	lim_cur = (uintmax_t)lim.rlim_cur;
	i = -1;
	while (src && src[++i])
		if ((uintmax_t)ft_atoi(src[i]) > lim_cur
				|| fcntl(ft_atoi(src[i]), F_GETFL) < 0)
		{
			display_bad_file_descriptor(STDERR_FILENO);
			return (-1);
		}
	if (dst && ((uintmax_t)ft_atoi(dst) > lim_cur
			|| fcntl(ft_atoi(dst), F_GETFL) < 0))
	{
		display_bad_file_descriptor(STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int	open_file_command_bis(t_redir **redir)
{
	int	verif;

	verif = 0;
	if ((*redir)->filename)
	{
		parser_var_simple(&((*redir)->filename), 1);
		verif = file_exist((*redir)->filename, (*redir)->type);
		open_file_great(*redir);
	}
	return (verif);
}

/*
** Verifie si c'est possible, puis ouvre les fds et creer les fichiers
** si besoin. Ensuite stock les nouvelles infos dans t_redir *redir
*/

int			open_file_command(t_redir *redir, t_pos *pos)
{
	int	verif;

	verif = 0;
	if (!redir)
		return (-1);
	verif = open_file_command_bis(&redir);
	if (verif != -1 && redir->type != DLESS
			&& verif_file_descriptor(redir->src_fd, redir->dest_fd) == -1)
		verif = -1;
	if (redir->type == DLESS)
		open_file_dless(redir, pos);
	if (verif > -1)
		verif = 0;
	else
		gest_return(1);
	return (verif);
}
