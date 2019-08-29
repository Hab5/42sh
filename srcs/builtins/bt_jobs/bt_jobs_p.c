/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_jobs_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:46:58 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

void		bt_jobs_p(t_job *j, int max_current)
{
	t_process	*p;

	(void)max_current;
	p = j->first_process;
	ft_dprintf(STDOUT_FILENO, "[%d]", j->process_id);
	while (p)
	{
		ft_dprintf(STDOUT_FILENO, " %d", p->pid);
		p = p->next;
	}
	ft_dprintf(STDOUT_FILENO, "\n");
}
