/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 06:46:41 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job.h"
#include "builtins.h"

int			launch_process(t_process *p, pid_t pgid, int fg)
{
	char	**environ;
	int		verif;

	environ = create_list_env(get_env(0, NULL), 1);
	config_pid_process(pgid, fg);
	redirection_fd(p->r);
	verif = execve(p->cmd_path, p->cmd, environ);
	display_command_not_found(p->r, p->cmd[0]);
	execve_bin_test();
	exit(verif);
}

void		whois_type(int type)
{
	if (type == LESS)
		ft_printf("type is LESS\n");
	if (type == DLESS)
		ft_printf("type is DLESS\n");
	if (type == GREAT)
		ft_printf("type is GREAT\n");
	if (type == DGREAT)
		ft_printf("type is DGREAT\n");
	if (type == AMPGREAT)
		ft_printf("type is AMPGREAT\n");
	if (type == GREATAMP)
		ft_printf("type is GREATAMP\n");
	if (type == LESSAMP)
		ft_printf("type is LESSAMP\n");
	if (type == LESSAMPHYPH)
		ft_printf("type is LESSAMPHYPH\n");
	if (type == GREATAMPHYPH)
		ft_printf("type is GREATAMPHYPH\n");
}

void		display_redirection(t_redirection *r)
{
	t_redirect	*redir;

	if (!r)
		return ;
	ft_printf("in = %d\n", r->in);
	ft_printf("out = %d\n", r->out);
	ft_printf("error = %d\n", r->error);
	redir = r->redirect;
	while (redir)
	{
		ft_printf("base = %d, new_fd = %d, type = %d\n",
			redir->base, redir->new_fd, redir->type);
		whois_type(redir->type);
		redir = redir->next;
	}
}

int			launch_job_fork(t_job *j, t_process *p, int fg)
{
	int	verif;

	verif = 0;
	if (p->cmd_path)
	{
		verif = launch_process(p, j->pgid, fg);
		execve_bin_test();
	}
	else
	{
		gest_return(12);
		execve_bin_test();
	}
	return (verif);
}

int			launch_job(t_job *j, int fg)
{
	t_process	*p;
	pid_t		pid;
	int			verif;

	p = j->first_process;
	verif = 0;
	while (p)
	{
		pid = fork();
		if (pid == 0)
			verif = launch_job_fork(j, p, fg);
		else if (pid < 0)
			display_error_fork(p->r);
		else
			edit_pid_shell(pid, j, p);
		p = p->next;
	}
	act_job(j, fg);
	return (verif);
}
