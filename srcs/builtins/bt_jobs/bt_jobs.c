/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/25 16:14:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

static void	display_jobs(void (*p)(t_job*, int), char **av)
{
	t_job	*j;
	int		max_current;

	max_current = get_shell()->max_job_current;
	if (!*av)
	{
		j = get_first_job(NULL);
		while (j)
		{
			if (job_is_completed(j) || job_is_stopped(j) || j->pgid > 0)
				(*p)(j, max_current);
			j = j->next;
		}
	}
	else
		display_jobs_options(p, av);
}

int			opt_bt_jobs(char *av)
{
	int	result;
	int	i;

	if (av[0] != '-' || (!av[1]))
		return (-1);
	i = 0;
	result = 0;
	while (av[++i])
	{
		if (av[i] == 'l')
			result = 1;
		else if (av[i] == 'p')
			result = 2;
		else if (av[i] == '-')
		{
			result = 3;
			break ;
		}
		else
		{
			result = 0;
			break ;
		}
	}
	return (result);
}

int			bt_jobs(t_job *j, char **av, t_redirection *r)
{
	int		result;
	void	(*p)(t_job*, int);

	redirection_fd(r);
	if (j->fg == 0)
	{
		display_no_job_control("jobs");
		return (1);
	}
	update_status();
	p = &bt_jobs_s;
	while (*(++av))
	{
		result = opt_bt_jobs(*av);
		if (result == 1)
			p = &bt_jobs_l;
		else if (result == 2)
			p = &bt_jobs_p;
		else
			break ;
	}
	display_jobs(p, av);
	return (0);
}
