/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:27:12 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"
#include "builtins.h"

/*
** Add path command and dysplay error
*/

int						is_not_builtin(t_job *j, t_process *p, int fg)
{
	int	verif;
	int	last_return;

	verif = 0;
	p->cmd_path = is_in_path(p->cmd[0], 1);
	last_return = check_last_command();
	verif = launch_job(j, fg);
	if (last_return == -6)
		verif = gest_return(-6);
	if (!(p->cmd_path))
		verif = gest_error_path(p->cmd[0], p->r);
	return (verif);
}

int						exec_ft_simple_command(t_job *j, t_process *p,
		t_pos *pos, int fg)
{
	int	verif;

	verif = 0;
	if (!builtin_exist(p->cmd[0]))
		verif = is_not_builtin(j, p, fg);
	else
	{
		verif = builtin(j, p, pos, fg);
		if (verif == -1)
			verif = is_not_builtin(j, p, fg);
	}
	return (verif);
}

/*
** Simple command
** Args: 	char **argv -> command
**			t_token *t ->
**			t_pos *pos -> know position terminal for fc builtin or heredocs
**			int bg -> if foreground bg = 0 or
**					if it's a background command -> ID background
*/

int						ft_simple_command(char **argv, t_token *t, t_pos *pos,
		int bg)
{
	int				fg;
	int				verif;
	t_job			*j;
	t_process		*p;

	if ((!argv) || (!*argv))
		return (-1);
	if (bg != 0)
		manage_id_job(bg);
	fg = (bg > 0) ? 0 : 1;
	j = create_new_job(argv, t, NULL, fg);
	p = j->first_process;
	p->final_str = ft_construct_redirection(t);
	if (check_last_command() == -5)
	{
		gest_return(1);
		clean_fuck_list(0);
		return (1);
	}
	verif = exec_ft_simple_command(j, p, pos, fg);
	return (verif);
}

int						ft_simple_command_fc(char *editor)
{
	char			**av;
	int				verif;
	t_job			*j;
	t_process		*p;
	t_redirection	*r;

	verif = 0;
	if (!(av = (char**)malloc(sizeof(char*) * 3)))
		return (-1);
	av[0] = ft_strdup(editor);
	av[1] = ft_strdup("/tmp/42sh-fc.file");
	av[2] = 0;
	r = init_redirection();
	j = create_new_job(av, NULL, r, 1);
	p = j->first_process;
	verif = is_not_builtin(j, p, 1);
	ft_arraydel(&av);
	return (verif);
}
