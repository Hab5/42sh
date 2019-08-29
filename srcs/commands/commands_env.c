/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 18:12:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"
#include "builtins.h"

/*
** Copy struct redirection to ft_simple_command_redirection
*/

static t_redirection	*cpy_redirection(t_redirection *r)
{
	t_redirection	*cpy;
	t_redirect		*head;

	if (!(cpy = (t_redirection*)malloc(sizeof(t_redirection) * 1)))
		return (NULL);
	cpy->in = r->in;
	cpy->out = r->out;
	cpy->error = r->error;
	cpy->redirect = ft_init_redirect();
	head = r->redirect;
	while (r->redirect && r->redirect->base != -1)
	{
		ft_create_maillon_redirect_env(cpy->redirect, r->redirect);
		r->redirect = r->redirect->next;
	}
	r->redirect = head;
	ft_create_maillon_redirect(cpy->redirect, -1,
			-1, NULL);
	return (cpy);
}

/*
** Simple command for set or env
** give a job for is_not_builtin command
** Args:	char **argv -> command
**			t_redirection *r -> struct to redirection of the command
**			t_pos *pos -> know position terminal for fc builtin or heredocs
**			int fg -> if 0 it's a background command. If 1 it's a foreground
**				command.
*/

int						ft_simple_command_redirection(char **argv,
		t_redirection *r, t_pos *pos, int fg)
{
	int				verif;
	t_job			*j;
	t_process		*p;
	t_redirection	*cpy;

	verif = 0;
	cpy = cpy_redirection(r);
	j = create_new_job(argv, NULL, cpy, fg);
	p = j->first_process;
	p->final_str = NULL;
	if (check_last_command() == -5)
	{
		gest_return(1);
		clean_fuck_list(0);
		return (1);
	}
	verif = exec_ft_simple_command(j, p, pos, fg);
	return (0);
}
