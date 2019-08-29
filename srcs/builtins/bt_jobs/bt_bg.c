/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 19:59:04 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

int			bt_bg(t_job *j, char **av, t_redirection *r)
{
	char	*cmd;
	t_job	*job_launch;

	redirection_fd(r);
	if (j->fg == 0)
	{
		display_no_job_control("bg");
		return (1);
	}
	job_launch = job_for_bg_fg(av);
	if (!job_launch)
		return (-2);
	change_fg_var_job(job_launch, 0);
	cmd = cmd_job_s(job_launch);
	if (cmd)
		ft_dprintf(STDOUT_FILENO, "%s\n", cmd);
	ft_strdel(&cmd);
	continue_job(job_launch, 0);
	return (0);
}
