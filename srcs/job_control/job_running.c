/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_running.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:52:06 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 09:42:55 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

int	jobs_running(void)
{
	t_job	*j;

	j = get_first_job(NULL);
	while (j)
	{
		if (job_is_stopped(j))
			return (1);
		j = j->next;
	}
	return (0);
}
