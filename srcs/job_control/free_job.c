/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:24:08 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 13:21:15 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

void		free_process(t_job **j)
{
	t_process	*p;
	t_process	*next;

	if ((!j) || (!(*j)))
		return ;
	p = (*j)->first_process;
	while (p)
	{
		next = p->next;
		ft_strdel(&(p->cmd_path));
		ft_strdel(&(p->final_str));
		if (p->cmd)
			ft_arraydel(&(p->cmd));
		free(p);
		p = NULL;
		p = next;
	}
}

void		free_job(t_job **j)
{
	if (j && (*j))
	{
		clean_file(*j);
		free_redirection(&((*j)->r));
		if ((*j)->current != 0)
		{
			edit_current_value((*j)->current);
			get_shell()->max_job_current -= 1;
		}
		if ((*j)->first_process)
			free_process(j);
		free(*j);
		(*j) = NULL;
	}
}

void		free_all_job(void)
{
	t_job	**j;
	t_job	*h;

	j = static_job();
	while (*j)
	{
		h = (*j)->next;
		free_job(&(*j));
		(*j) = h;
	}
}
