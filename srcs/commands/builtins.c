/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:03:25 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "job.h"

int			prepare_verif_syntax_key(char *cmd)
{
	char	*value;
	int		index;

	index = ft_chr_index(cmd, '=');
	if (index > 0)
	{
		value = ft_strsub(cmd, 0, index);
		if (verif_syntax_key(value))
		{
			ft_strdel(&value);
			return (1);
		}
		ft_strdel(&value);
	}
	return (0);
}

int			builtin_exist(char *cmd)
{
	if (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd") || ft_strequ(cmd, "exit")
		|| ft_strequ(cmd, "fc") || ft_strequ(cmd, "test")
		|| ft_strequ(cmd, "alias") || ft_strequ(cmd, "unalias")
		|| ft_strequ(cmd, "hash") || ft_strequ(cmd, "type")
		|| ft_strequ(cmd, "jobs") || ft_strequ(cmd, "fg")
		|| ft_strequ(cmd, "bg") || ft_strequ(cmd, "set")
		|| ft_strequ(cmd, "export") || ft_strequ(cmd, "unset")
		|| (ft_strchr_exist(cmd, '=') && prepare_verif_syntax_key(cmd)))
		return (1);
	return (0);
}

/*
** Folowing of launch_job_blt function
*/

int			launch_process_blt(t_job *j, t_process *p, t_pos *pos,
				int fg)
{
	int		verif;

	config_pid_process(j->pgid, fg);
	redirection_fd(p->r);
	verif = is_builtin(j, p, pos);
	execve_bin_test();
	exit(verif);
}

/*
** launch builtin in fork if is background command
*/

int			launch_job_blt(t_job *j, t_process *p, t_pos *pos, int fg)
{
	pid_t		pid;
	int			verif;

	verif = 0;
	pid = fork();
	if (pid == 0)
		verif = launch_process_blt(j, p, pos, fg);
	else if (pid < 0)
		display_error_fork(p->r);
	else
		edit_pid_shell(pid, j, p);
	p = p->next;
	act_job(j, fg);
	return (verif);
}

/*
** Launch builtin command
*/

int			builtin(t_job *j, t_process *p, t_pos *pos, int fg)
{
	int		verif;

	verif = -1;
	if (fg == 1)
		return (is_builtin(j, p, pos));
	else
		verif = launch_job_blt(j, p, pos, fg);
	return (verif);
}
