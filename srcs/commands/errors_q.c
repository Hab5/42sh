/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:07:15 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

void	display_error_tc(t_redirection *r, char *name)
{
	ft_dprintf(r->error, "%s: error: %s\n", get_shell()->name_shell, name);
}

void	display_other_error(int fd_error, char *name, char *error)
{
	ft_dprintf(fd_error, "%s: %s: %s\n", get_shell()->name_shell, name, error);
}

void	display_error_expansion(char *src)
{
	ft_dprintf(STDERR_FILENO, "%s: ${%s}: bad substitution\n",
			get_shell()->name_shell, src);
	gest_return(-5);
}

void	display_error_syntax(char *key, char *value)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s: syntax error: operand expected\n",
			get_shell()->name_shell, key, value);
	gest_return(-5);
}
