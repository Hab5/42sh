/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 19:58:58 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

void	display_invalid_option_job(t_redirection *r, char *name)
{
	char	c;

	c = 0;
	while (*name)
	{
		if (*name != 'p' && *name != 'l')
		{
			c = *name;
			break ;
		}
		++name;
	}
	ft_dprintf(r->error, "%s: jobs -%c: invalid option\n",
			get_shell()->name_shell, c);
	ft_dprintf(r->error, "jobs: usage: jobs [-l | -p] [job_id...]\n");
}

void	display_no_current_job(char *name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: no current job\n",
			get_shell()->name_shell, name);
}

void	display_no_job_control(char *name)
{
	char	*data;
	char	*cache;

	cache = ft_strjoin("42sh: ", name);
	data = ft_strjoin(cache, ": no job control\n");
	ft_putstr_fd(data, STDERR_FILENO);
	ft_strdel(&cache);
	ft_strdel(&data);
}

void	display_job_stopped(void)
{
	ft_dprintf(STDERR_FILENO, "%s: There are stopped jobs.\n",
			get_shell()->name_shell);
}

void	display_kill_not_work(t_redirection *r, char *name)
{
	ft_dprintf(r->error, "%s: %s: Kill not work!\n",
			get_shell()->name_shell, name);
}
