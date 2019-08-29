/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:39:52 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** Return exit code value of last command
*/

int	check_last_command(void)
{
	char	*str;
	int		check;

	str = value_line_path("?", 0);
	check = (str) ? ft_atoi(str) : 0;
	ft_strdel(&str);
	return (check);
}

int	check_is_exec(char *src, t_redirection *r)
{
	char	*str;

	if (!src)
		return (1);
	if (ft_strequ(src, "env") || ft_strequ(src, "set")
		|| ft_strequ(src, "setenv") || ft_strequ(src, "unsetenv")
		|| ft_strequ(src, "export") || ft_strequ(src, "unset")
		|| ft_strequ(src, "exit") || ft_strchr_exist(src, '=')
		|| ft_strequ(src, "echo") || ft_strequ(src, "cd")
		|| ft_strequ(src, "jobs") || ft_strequ(src, "fg")
		|| ft_strequ(src, "bg") || ft_strequ(src, "fc"))
		return (1);
	str = is_in_path(src, 1);
	if (!str)
	{
		gest_return(gest_error_path(src, r));
		return (0);
	}
	ft_strdel(&str);
	return (1);
}
