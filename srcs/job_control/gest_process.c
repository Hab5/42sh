/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:34:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 22:36:46 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"
#include <errno.h>

/*
** check mark_process_status
** WIFSIGNALED -> check if process exist
** WIFSTOPPED -> True if the process has not terminated, but has stopped
**					and can be restarted.
*/

static int	action_process_status(t_job *j, pid_t pid, int status, t_process *p)
{
	if (p->pid == pid)
	{
		p->status = status;
		if (WIFSTOPPED(status))
			p->stopped = 1;
		else if (WIFCONTINUED(status))
		{
			j->notified = 0;
			p->stopped = 0;
		}
		else
		{
			p->completed = 1;
			if ((!j->notified) && WIFSIGNALED(status)
					&& (WTERMSIG(status) == 3))
				j->notified = 1;
		}
		return (0);
	}
	return (1);
}

/*
** edit status process and edit variable if a process is stopped or finished
** ARGS:	pid_t pid -> pid to check
**			int status -> edit status process
*/

int			mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		j = get_first_job(NULL);
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (action_process_status(j, pid, status, p) == 0)
					return (0);
				p = p->next;
			}
			j = j->next;
		}
		ft_dprintf(STDERR_FILENO, "%s: No child process %d.\n",
			get_shell()->name_shell, pid);
		return (-1);
	}
	return (-1);
}

int			choice_gest_return(t_job *j, int status)
{
	t_process	*p;
	char		*str;

	if (WIFSTOPPED(status))
		return (146);
	if (status != 256 && status != 13)
		return (status);
	p = j->first_process;
	while (p->next)
		p = p->next;
	str = is_in_path(p->cmd[0], 1);
	if (str)
	{
		ft_strdel(&str);
		return (1);
	}
	else
		return ((check_last_command() == -6) ? 126 : 127);
}

/*
** Update all process of job-control
** WUNTRACED: revenir si fils bloqué
** WNOHANG: revenir immédiatement si aucun fils n'est achevé.
*/

void		update_status(void)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG | WCONTINUED);
		if (mark_process_status(pid, status))
			break ;
	}
}

/*
** wait job until it is stopped or finished
** ARG:		t_job *j -> struct of commands
*/

void		wait_for_job(t_job *j)
{
	int		pass;
	int		status;
	pid_t	pid;

	status = 0;
	pass = 0;
	while (1)
	{
		++pass;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (mark_process_status(pid, status) || job_is_stopped(j)
			|| job_is_completed(j))
			break ;
	}
	if (WIFSTOPPED(status))
		gest_return(WSTOPSIG(status));
	else if (WIFSIGNALED(status))
		gest_return(WTERMSIG(status));
	else
		gest_return(status);
}
