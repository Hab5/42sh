/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_redir_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 18:23:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "job.h"

void		restore_redirection(void)
{
	char	*fd_s;
	int		fd;

	fd_s = value_line_path("STDIN", 0);
	fd = ft_atoi(fd_s);
	ft_strdel(&fd_s);
	dup2(fd, STDIN_FILENO);
	fd_s = value_line_path("STDOUT", 0);
	fd = ft_atoi(fd_s);
	ft_strdel(&fd_s);
	dup2(fd, STDOUT_FILENO);
	fd_s = value_line_path("STDERR", 0);
	fd = ft_atoi(fd_s);
	ft_strdel(&fd_s);
	dup2(fd, STDERR_FILENO);
}

/*
** if builtin not exist return -1
** if exist and good execution return 0 otherwise return -2
*/

void		restore_and_return_builtin(int verif)
{
	restore_redirection();
	if (verif == -2)
		gest_return(1);
	else
	{
		gest_return(verif);
	}
}
