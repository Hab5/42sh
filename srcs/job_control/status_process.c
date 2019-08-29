/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:34:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 20:50:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"
#include <errno.h>

/*
** Parcours chaque process d'un job et utilise la fonction
**	display_stat_process pour afficher le status d'un process
**	si besoin
** Args:	t_job *j -> process a check
*/

void		notif_stop(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (WIFSIGNALED(p->status) && WTERMSIG(p->status) != p->last_status)
			bt_jobs_s(j, get_shell()->max_job_current);
		else if (WIFSTOPPED(p->status) && (!j->notified))
		{
			j->notified = 1;
			bt_jobs_s(j, get_shell()->max_job_current);
		}
		p->last_status = p->status;
		p = p->next;
	}
}

void		job_notif(void)
{
	t_job	*j;

	update_status();
	j = get_first_job(NULL);
	while (j)
	{
		if (job_is_completed(j) && (j->fg == 0
					|| (j->fg && j->first_process->stopped == 1)))
			bt_jobs_s(j, get_shell()->max_job_current);
		else if (job_is_stopped(j))
			notif_stop(j);
		else if (WIFSIGNALED(j->first_process->status)
				&& WTERMSIG(j->first_process->status) != 1
				&& WTERMSIG(j->first_process->status) != 13)
			bt_jobs_s(j, get_shell()->max_job_current);
		j = j->next;
	}
	clean_fuck_list(0);
}

void		job_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void		continue_job(t_job *j, int fg)
{
	job_running(j);
	j->notif_stop = 0;
	if (fg)
		add_in_fg(j, 1);
	else
		add_in_bg(j, 1);
	clean_fuck_list(0);
}
