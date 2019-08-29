/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:57:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 21:57:27 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "job.h"

/*
** display error command
** if the value of ? is equal to -6 display "Permission denied"
** otherwise display "command not found"
** Args:	char *cmd -> name of the command
**			t_redirection *r -> structure to redirection
*/

int			gest_error_path(char *cmd, t_redirection *r)
{
	struct stat sb;

	if (check_last_command() == -6)
	{
		display_permission_denied(r, cmd);
		gest_return(126);
		return (126);
	}
	if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_dprintf(r->error, "42sh: %s: Is a directory\n", cmd);
		gest_return(126);
		return (126);
	}
	display_command_not_found(r, cmd);
	gest_return(127);
	return (127);
}

/*
** edit the local variable ('?') for know if the last command
** has worked
*/

int			gest_return(int verif)
{
	char	*value;

	if (verif == 13)
		return (126);
	if (verif > 1 && verif < 23)
		verif = 128 + verif;
	if (verif > 255)
		verif %= 255;
	if (verif == 30)
		verif = 2;
	value = ft_itoa(verif);
	verif = add_set_value("?", value);
	ft_strdel(&value);
	return (verif);
}

/*
** is_end = 1 -> free env
** t_env *head is not null -> modify head of the env
*/

t_env		*get_env(int is_end, t_env *head)
{
	static t_env	*my_env;

	if (is_end == 3 && (!my_env))
		return (NULL);
	if ((!my_env) && (!head))
	{
		my_env = init_env();
		init_variable();
	}
	if (head)
		my_env = head;
	if (is_end == 1)
		free_env(&my_env);
	return (my_env);
}
