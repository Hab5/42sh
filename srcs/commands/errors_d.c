/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:05:48 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

void	display_too_many_arg(t_redirection *r, char *name)
{
	ft_dprintf(r->error, "%s: %s: Too many arguments.\n",
			get_shell()->name_shell, name);
}

void	display_too_few_arg(t_redirection *r, char *name)
{
	ft_dprintf(r->error, "%s: %s: Too few arguments.\n",
			get_shell()->name_shell, name);
}

void	display_nothing_value(t_redirection *r, char *name)
{
	ft_dprintf(r->error, "%s: %s: You are nothing value\n",
			get_shell()->name_shell, name);
}

void	display_bad_file_descriptor(int error)
{
	ft_dprintf(error, "%s: Bad file descriptor\n", get_shell()->name_shell);
}

void	display_no_such_job(char *name_blt, char *name)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: no such job\n",
			get_shell()->name_shell,
		name_blt, name);
}
