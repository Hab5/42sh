/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 18:48:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

char		*cmd_job_s(t_job *j)
{
	t_process	*p;
	char		*str;
	char		*cache;

	p = j->first_process;
	str = 0;
	while (p)
	{
		assembly_command_s(p, &str);
		p = p->next;
	}
	if (j->fg == 0)
	{
		cache = ft_strjoin(str, " &");
		ft_strdel(&str);
		str = cache;
	}
	return (str);
}

/*
** WTERMSIG(j->first_process->status));
** LINE 47:
** else
** 	str = ft_itoa(sig);
*/

char		*ft_inter_signal_4(int sig)
{
	char	*str;

	str = NULL;
	if (sig == 22)
		str = ft_strdup("Stopped(SIGTTOU)");
	else if (sig == 23)
		str = ft_strdup("Discard(SIGIO)");
	else if (sig == 24)
		str = ft_strdup("Terminated(SIGXCPU)");
	else if (sig == 25)
		str = ft_strdup("Terminated(SIGXFSZ)");
	else if (sig == 26)
		str = ft_strdup("Terminated(SIGVTALRM)");
	else if (sig == 27)
		str = ft_strdup("Terminated(SIGPROF)");
	else if (sig == 28)
		str = ft_strdup("Discard(SIGWINCH)");
	else if (sig == 29)
		str = ft_strdup("Discard(SIGINFO)");
	else if (sig == 30)
		str = ft_strdup("Terminated(SIGUSR1)");
	else if (sig == 31)
		str = ft_strdup("Terminated(SIGUSR2)");
	return (str);
}

char		*ft_inter_signal_3(int sig)
{
	char	*str;

	str = NULL;
	if (sig == 13)
		str = ft_strdup("Terminated(SIGPIPE)");
	else if (sig == 14)
		str = ft_strdup("Terminated(SIGALRM)");
	else if (sig == 15)
		str = ft_strdup("Terminated(SIGTERM)");
	else if (sig == 16)
		str = ft_strdup("Discard(SIGURG)");
	else if (sig == 17)
		str = ft_strdup("Stopped(SIGSTOP)");
	else if (sig == 18)
		str = ft_strdup("Stopped(SIGTSTP)");
	else if (sig == 19)
		str = ft_strdup("Running(SIGCONT)");
	else if (sig == 20)
		str = ft_strdup("Terminated(SIGCHLD)");
	else if (sig == 21)
		str = ft_strdup("Stopped(SIGTTIN)");
	else if (sig > 21)
		str = ft_inter_signal_4(sig);
	return (str);
}

char		*ft_inter_signal_2(int sig)
{
	char	*str;

	str = NULL;
	if (sig == 4)
		str = ft_strdup("Terminated(SIGILL)");
	else if (sig == 5)
		str = ft_strdup("Terminated(SIGTRAP)");
	else if (sig == 6)
		str = ft_strdup("Terminated(SIGABRT)");
	else if (sig == 7)
		str = ft_strdup("Terminated(SIGEMT)");
	else if (sig == 8)
		str = ft_strdup("Terminated(SIGFPE)");
	else if (sig == 9)
		str = ft_strdup("Terminated(SIGKILL)");
	else if (sig == 10)
		str = ft_strdup("Terminated(SIGBUS)");
	else if (sig == 11)
		str = ft_strdup("Terminated(SIGSEGV)");
	else if (sig == 12)
		str = ft_strdup("Terminated(SIGSYS)");
	else if (sig > 12)
		str = ft_inter_signal_3(sig);
	return (str);
}

char		*ft_inter_signal(int sig, t_job *j)
{
	char	*str;

	str = NULL;
	if (sig == 0 && j->first_process->last_status > 0
			&& job_is_completed(j) && j->fg == 1)
		str = ft_strdup("Terminated: 15");
	else if (sig == 0 && job_is_completed(j) && j->fg == 0)
		str = ft_strdup("Done\t\t");
	else if (sig == 0 && j->fg == 0
			&& (!job_is_completed(j)) && (!job_is_stopped(j)))
		str = ft_strdup("Running\t\t");
	else if (sig == 1)
		str = ft_strdup("Done(SIGHUP)");
	else if (sig == 2)
		str = ft_strdup("Terminated(SIGINT)");
	else if (sig == 3)
		str = ft_strdup("Terminated(SIGQUIT)");
	else if (sig > 3)
		str = ft_inter_signal_2(sig);
	else if (sig != 0)
		str = ft_itoa(sig);
	return (str);
}
