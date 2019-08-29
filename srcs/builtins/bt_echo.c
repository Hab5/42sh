/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:19:28 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 13:54:23 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	echo_arg(char **av)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 1;
	while (av[i] != NULL)
	{
		if (av[i][0] != '-')
			break ;
		j = 1;
		while (av[i][j] != '\0' && av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break ;
		n++;
		i++;
	}
	return (n);
}

int			bt_echo(char **av, t_redirection *r)
{
	int	i;
	int	arg_n;

	redirection_fd(r);
	if (fcntl(STDOUT_FILENO, F_GETFL) < 0)
		return (1);
	i = 1;
	arg_n = echo_arg(av);
	i += arg_n;
	while (av[i] != NULL)
	{
		ft_dprintf(STDOUT_FILENO, "%s", av[i]);
		if (av[i + 1] != NULL)
			ft_dprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (!arg_n)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (0);
}
