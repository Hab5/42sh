/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:10:27 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** in -> STDIN_FILENO
** out -> STDOUT_FILENO
** error -> STDERR_FILLENO
*/

void	redir_in(t_redirection *r)
{
	if (r->in != STDIN_FILENO)
		if (dup2(r->in, STDIN_FILENO) == -1)
			exit(-1);
}

void	redir_out(t_redirection *r)
{
	if (r->out != STDOUT_FILENO)
		if (dup2(r->out, STDOUT_FILENO) == -1)
			exit(-1);
}

void	redir_error(t_redirection *r)
{
	if (r->error != STDERR_FILENO)
		if (dup2(r->error, STDERR_FILENO) == -1)
			exit(-1);
}

/*
** dup2(src, new_fd);
** if (verif_close(src))
**	close(src);
*/

void	other_redir(t_redirect *r)
{
	int	new_fd;
	int	src;

	new_fd = r->new_fd;
	src = r->base;
	if (new_fd == -1)
		return ;
	if (src != new_fd)
	{
		if (dup2(new_fd, src) == -1)
			exit(-1);
		if (verif_close(new_fd))
			close(new_fd);
	}
}

void	redirection_fd_bis(t_redirection *r)
{
	standard_redirection(r);
	if (verif_close(r->in) && ft_fd_redirect_exist(r->redirect, STDIN_FILENO))
		close(r->in);
	if (verif_close(r->out) && ft_fd_redirect_exist(r->redirect, STDOUT_FILENO))
		close(r->out);
	if (verif_close(r->error)
		&& ft_fd_redirect_exist(r->redirect, STDERR_FILENO))
		close(r->error);
}
