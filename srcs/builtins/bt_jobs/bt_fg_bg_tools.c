/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg_bg_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 16:28:27 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

/*
** Find option for fg or bg command
*/

static t_job	*job_for_bg_fg_opt(char **av)
{
	t_job	*j;
	t_job	*job_launch;
	int		i;

	j = get_first_job(NULL);
	job_launch = NULL;
	i = 1;
	if (ft_strequ(*av, "--"))
		++i;
	while (av[i])
	{
		j = search_job(av[i]);
		if (j)
		{
			if (job_is_completed(j) || job_is_stopped(j) || j->pgid > 0)
				job_launch = j;
			else
				display_no_such_job(av[0], av[i]);
		}
		else
			display_no_such_job(av[0], av[i]);
		++i;
	}
	return (job_launch);
}

/*
** Select job to launch for fg or bg command
*/

t_job			*job_for_bg_fg(char **av)
{
	t_job	*j;
	t_job	*job_launch;

	update_status();
	if (!av[1])
	{
		job_launch = NULL;
		j = get_first_job(NULL);
		while (j)
		{
			if (j->first_process->stopped == 1 || j->pgid > 0)
				job_launch = j;
			j = j->next;
		}
		if (!job_launch)
			display_no_current_job(av[0]);
	}
	else
		job_launch = job_for_bg_fg_opt(av);
	return (job_launch);
}

/*
** Change fg variable on all process if the user use fg or bg command
** Args:	t_job *j:	edit variable in this job
**			int fg:		value variable
*/

void			change_fg_var_job(t_job *j, int fg)
{
	t_process	*p;

	j->fg = fg;
	p = j->first_process;
	while (p)
	{
		p->fg = fg;
		p = p->next;
	}
}
