/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/07/05 02:17:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

/*
** int			edit_fd(int base, int origin, int new)
** {
** 	if (base == origin)
** 		return (new);
** 	if (verif_close(new))
** 		close(new);
** 	return (base);
** }
*/

void		pipe_deplace_fd(t_job *j, t_process *p, int fd)
{
	if (p->r->in == j->r->in)
		p->r->in = fd;
	else
	{
		if (fd != j->r->in && verif_close(fd))
			close(fd);
	}
}
