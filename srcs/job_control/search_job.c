/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/24 02:39:07 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

/*
** Retourne le dernier job si il ne trouve rien retourne NULL
*/

t_job	*last_jobs(void)
{
	t_job	*j;
	int		max_current;

	max_current = get_shell()->max_job_current;
	j = get_first_job(NULL);
	while (j)
	{
		if (j->current == max_current)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
** Retourne l'avant dernier job si il ne le trouve pas, appel last_jobs
** pour retourner le dernier
*/

t_job	*previous_jobs(void)
{
	t_job	*j;
	int		max_current;

	max_current = get_shell()->max_job_current - 1;
	if (max_current == 0)
		++max_current;
	j = get_first_job(NULL);
	while (j)
	{
		if (j->current == max_current)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
** Retourne le job dont le j->pgid a la meme valeur que le parametre pid
*/

t_job	*ft_search_pid_job(pid_t pid)
{
	t_job	*job;

	job = get_first_job(NULL);
	while (job)
	{
		if (job->pgid == pid)
			return (job);
		job = job->next;
	}
	return (NULL);
}

/*
** Retourne le job dont l'id du job demande
** Args:	char *av -> un argument du builtin
**			int index -> l'endroit ou on doit extraire la valeur de l'id
*/

t_job	*ft_search_id_job(char *av, int index)
{
	t_job	*job;
	int		id;

	id = ft_atoi(av + index);
	job = get_first_job(NULL);
	while (job)
	{
		if (job->process_id == id)
			return (job);
		job = job->next;
	}
	return (NULL);
}

/*
** Retourne le job recherche si il est unique sinon retourne NULL
** Args:	char *av -> un argument du builtin
**			int index -> l'endroit ou on doit extraire la valeur de l'id
*/

t_job	*ft_search_str_job(char *av, int index)
{
	t_job	*job;
	t_job	*final;
	char	*str;

	job = get_first_job(NULL);
	final = NULL;
	while (job)
	{
		if (job->first_process && job->first_process->cmd)
		{
			str = ft_strnstr(job->first_process->cmd[0], av + index,
					ft_strlen(av + index));
			if (str)
			{
				if (final)
					return (NULL);
				else
					final = job;
			}
		}
		job = job->next;
	}
	return (final);
}
