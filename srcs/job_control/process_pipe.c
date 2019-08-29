/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:40:59 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job.h"
#include "builtins.h"

static void	launch_process_pipe(t_process *p)
{
	char	**environ;

	environ = create_list_env(get_env(0, NULL), 1);
	redirection_fd(p->r);
	execve(p->cmd_path, p->cmd, environ);
	exit(1);
}

static int	exec_pipe(t_job *j, t_process *p, int fg)
{
	int	verif;

	verif = 0;
	config_pid_process(j->pgid, fg);
	if (p->return_value == 1)
	{
		execve_bin_test();
		exit(1);
	}
	if ((verif = is_builtin(j, p, NULL)) == -1)
	{
		p->cmd_path = is_in_path(p->cmd[0], 1);
		if (p->cmd_path)
			launch_process_pipe(p);
		else
			display_command_not_found(p->r, p->cmd[0]);
	}
	execve_bin_test();
	exit(verif);
}

static void	fork_pipe(t_job *j, t_process *p, int fg, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd[0] != p->r->in && fd[0] != STDIN_FILENO && verif_close(fd[0]))
			close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (verif_close(fd[1]))
			close(fd[1]);
		exec_pipe(j, p, fg);
	}
	else if (pid < 0)
	{
		display_error_fork(j->r);
		exit(1);
	}
	else
		edit_pid_shell(pid, j, p);
}

static void	pipe_error(int error)
{
	ft_dprintf(error, "%s: error pipe\n", get_shell()->name_shell);
	bt_exit(NULL, NULL, NULL);
}

/*
** LINE 221: fd[0] = j->r->in;//open(STDIN_FILENO, O_RDWR);// j->r->in;
*/

void		launch_job_pipe(t_job *j, int fg)
{
	t_process	*p;
	int			fd[2];

	p = j->first_process;
	fd[0] = STDIN_FILENO;
	while (p)
	{
		if (p->next)
			if (pipe(fd) == -1)
				pipe_error(j->r->error);
		fork_pipe(j, p, fg, fd);
		if (p->r->in != j->r->in && verif_close(p->r->in))
			close(p->r->in);
		if (fd[1] != j->r->out && verif_close(fd[1]))
			close(fd[1]);
		p = p->next;
		if (p)
			pipe_deplace_fd(j, p, fd[0]);
	}
	act_job(j, fg);
}
