/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:24:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 13:21:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

static void	clean_close_fd(t_job *j)
{
	int	i;

	if (j->len_close && j->len_close > 0)
	{
		i = -1;
		while (++i < j->len_close)
			if (verif_close(j->close_fd[i]))
				close(j->close_fd[i]);
	}
	if (j->close_fd)
	{
		free(j->close_fd);
		j->close_fd = NULL;
	}
}

void		clean_redirection(t_redirection *r)
{
	if (r->in != STDIN_FILENO)
		if (verif_close(r->in))
			close(r->in);
	if (r->out != STDOUT_FILENO)
		if (verif_close(r->out))
			close(r->out);
	if (r->error != STDERR_FILENO)
		if (verif_close(r->error))
			close(r->error);
	delete_redirection(&r);
}

void		clean_file(t_job *j)
{
	t_process	*p;

	clean_close_fd(j);
	p = j->first_process;
	while (p && p->r)
	{
		clean_redirection(p->r);
		p = p->next;
	}
}

void		free_redirection(t_redirection **r)
{
	if (r && *r)
	{
		free(*r);
		(*r) = NULL;
	}
}
