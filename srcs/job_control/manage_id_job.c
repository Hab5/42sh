/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_id_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:34:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 12:58:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "env.h"

int	id_job(int value, int action)
{
	static int	id;

	if (action > 0)
		id = value;
	else if (action < 0)
		++id;
	return (id);
}

int	manage_id_job(int action)
{
	static int	last;
	t_job		*j;
	int			value;

	if (action > 0 && last != action)
	{
		last = action;
		return (id_job(0, -1));
	}
	else if (action == 0)
		last = 0;
	if (action <= 0)
	{
		j = get_first_job(NULL);
		value = 0;
		while (j)
		{
			if (j->pgid > 0)
				value = j->process_id;
			j = j->next;
		}
		id_job(value, 1);
	}
	return (id_job(0, 0));
}
