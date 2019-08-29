/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 01:41:22 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job.h"
#include "builtins.h"

void	config_pid_process(pid_t pgid, int fg)
{
	t_shell	*s;
	pid_t	pid;

	s = get_shell();
	if (s->interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		if (setpgid(pid, pgid) == -1)
			exit(1);
		if (fg)
			tcsetpgrp(s->term, pgid);
		dfl_signaux();
	}
}

void	act_job(t_job *j, int fg)
{
	t_shell	*shell;

	shell = get_shell();
	if (!shell->interactive)
		wait_for_job(j);
	else if (fg)
		add_in_fg(j, 0);
	else
	{
		bt_jobs_p(j, 0);
		add_in_bg(j, 0);
	}
}

void	edit_pid_shell(int pid, t_job *j, t_process *p)
{
	p->pid = pid;
	if (get_shell()->interactive)
	{
		if (!(j->pgid))
			j->pgid = pid;
		if (setpgid(pid, j->pgid) == -1)
			exit(1);
	}
}
