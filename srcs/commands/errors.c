/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:07:18 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

void	execve_bin_test(void)
{
	char	**test;

	if (!(test = (char**)malloc(sizeof(char*) * 2)))
		return ;
	test[0] = ft_strdup("test");
	test[1] = 0;
	execve("/bin/test", test, NULL);
	ft_arraydel(&test);
}

char	*name_exec_error(void)
{
	char	*name_exec;

	name_exec = ft_strjoin(get_shell()->name_shell, ": ");
	return (name_exec);
}

void	display_command_not_found(t_redirection *r, char *cmd)
{
	char	*name_exec;
	char	*display;
	char	*cache;

	name_exec = name_exec_error();
	cache = ft_strjoin(name_exec, cmd);
	ft_strdel(&name_exec);
	display = ft_strjoin(cache, ": command not found\n");
	ft_putstr_fd(display, r->error);
	ft_strdel(&display);
	ft_strdel(&cache);
}

void	display_permission_denied(t_redirection *r, char *cmd)
{
	char	*name_exec;
	char	*display;
	char	*cache;

	name_exec = name_exec_error();
	cache = ft_strjoin(name_exec, cmd);
	ft_strdel(&name_exec);
	display = ft_strjoin(cache, ": Permission denied\n");
	ft_putstr_fd(display, r->error);
	ft_strdel(&display);
	ft_strdel(&cache);
}

void	display_error_fork(t_redirection *r)
{
	ft_dprintf(r->error, "%s: Error fork\n", get_shell()->name_shell);
}
