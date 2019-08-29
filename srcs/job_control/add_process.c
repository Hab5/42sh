/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/23 05:34:09 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

t_job	*get_end_job(void)
{
	t_job	*j;

	j = get_first_job(NULL);
	if (!j)
		return (NULL);
	while (j->next)
		j = j->next;
	return (j);
}

void	add_process(char **av, t_token *t, int fg)
{
	t_job		*j;
	t_process	*p;

	j = get_end_job();
	p = j->first_process;
	while (p)
	{
		if (!p->next)
		{
			p->next = init_process();
			p = p->next;
			break ;
		}
		p = p->next;
	}
	p->cmd = ft_arraydup(av);
	parser_var(&(p->cmd));
	p->fg = fg;
	p->r = (t) ? fill_redirection(t) : NULL;
	p->final_str = ft_construct_redirection(t);
}
