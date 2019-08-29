/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 13:59:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:29:42 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "sh21.h"

/*
** Decrement j->current if lower than value to know the last launch job
*/

void		edit_current_value(int value)
{
	t_job	*j;

	j = get_first_job(NULL);
	while (j)
	{
		if (j->current > value)
			j->current -= 1;
		j = j->next;
	}
}

/*
** Donne un id au dernier job, si il n'en a pas deja un, puis decrementer la
** valeur de j->current pour les commandes qui sont en dessous de la valeur
** du pgid donner en parametre
** Args:	pid_t pgid -> valeur du process a comparer
**			t_job *new_job -> le nouveau job dont la valeur doit etre
**				initialiser a la valeur max_job_current + 1
*/

static void	assign_value_current(pid_t pgid, t_job *new_job)
{
	t_shell	*shell;
	t_job	*j;
	int		max;
	int		min;

	shell = get_shell();
	if (new_job->current == 0)
	{
		shell->max_job_current += 1;
		new_job->current = shell->max_job_current;
	}
	j = get_first_job(NULL);
	max = shell->max_job_current;
	while (j)
	{
		if (j->pgid == pgid)
		{
			min = j->current;
			j->current = max + 1;
		}
		j = j->next;
	}
	edit_current_value(min);
}

static void	init_process_before_launch(t_process *p)
{
	while (p)
	{
		p->status = 0;
		p->stopped = 0;
		p = p->next;
	}
}

/*
** Launch job in foreground
** Args:	t_job *j -> process to launch in foreground
**			int value -> kill process if value is different from 0
*/

void		add_in_fg(t_job *j, int value)
{
	t_shell		*shell;
	t_process	*p;

	if (j->pgid < 1)
		exit(-1);
	assign_value_current(j->pgid, j);
	p = j->first_process;
	shell = get_shell();
	if (tcsetpgrp(shell->term, j->pgid) == -1)
		display_error_tc(j->r, "tcsetpgrp");
	if (value)
		kill_pgid(shell, j);
	init_process_before_launch(p);
	j->notified = 0;
	wait_for_job(j);
	if (tcsetpgrp(shell->term, shell->pgid) == -1)
		display_error_tc(j->r, "tcsetpgrp");
	if (tcgetattr(shell->term, &j->tmodes) == -1)
		display_error_tc(j->r, "tcgetattr");
	if (tcsetattr(shell->term, TCSADRAIN, &(shell->term_shell)) == -1)
		display_error_tc(j->r, "tcsetattr");
}

/*
** Launch job in background
** Args:	t_job *j -> process to launch in background
**			int value -> kill process if value is different from 0
*/

void		add_in_bg(t_job *j, int value)
{
	char		*itoa_pid;
	t_process	*p;

	if (j->pgid < 1)
		exit(-1);
	assign_value_current(j->pgid, j);
	if (tcgetattr(get_shell()->term, &j->tmodes) == -1)
		display_error_tc(j->r, "tcsetattr");
	p = j->first_process;
	init_process_before_launch(p);
	while (p)
	{
		if (!p->next)
			break ;
		p = p->next;
	}
	itoa_pid = ft_itoa(p->pid);
	add_set_value("!", itoa_pid);
	if (value)
		if (kill(-j->pgid, SIGCONT) < 0)
			display_kill_not_work(j->r, "bg");
	ft_strdel(&itoa_pid);
}
