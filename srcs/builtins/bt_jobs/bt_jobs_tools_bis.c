/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs_tools_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 18:13:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

char		*ft_name_sig(int sig)
{
	char	*str;

	str = NULL;
	if (sig == 0)
		str = ft_strdup("Running");
	else if ((sig >= 1 && sig <= 16) || sig == 20 || (sig >= 23 && sig <= 31))
		str = ft_strdup("Terminated");
	else if (sig == 17 || sig == 18 || sig == 21 || sig == 22)
		str = ft_strdup("Stopped");
	else if (sig == 19)
		str = ft_strdup("Running");
	return (str);
}

/*
** for %? search if av exist in job-control
** Args:	t_job *job:		search for this job
**			t_job **final:	stock the job found here
**			...:			see ft_search_exist_job
** Return:	0 if 0 or 1 process are found and
**				if final variable is not initialize
**			1 if final variable is already initialized
*/

static int	ft_search_exist_in_process(t_job *job, t_job **final,
			char *av, int index)
{
	t_process	*p;
	char		*str;
	int			i;

	p = job->first_process;
	i = -1;
	if ((!p) || (!p->cmd))
		return (0);
	while (p->cmd[++i])
	{
		str = ft_strstr(p->cmd[i], av + index + 1);
		if (str)
		{
			if (*final)
				return (1);
			else
				*final = job;
		}
	}
	return (0);
}

/*
** Search av on all job for `?%`
** Args:	char *av:	key
**			int index:	start character to search
*/

t_job		*ft_search_exist_job(char *av, int index)
{
	t_job		*job;
	t_job		*final;

	job = get_first_job(NULL);
	final = NULL;
	while (job->next)
	{
		if (ft_search_exist_in_process(job, &final, av, index))
			return (NULL);
		job = job->next;
	}
	return (final);
}
