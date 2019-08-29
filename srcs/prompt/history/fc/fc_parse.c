/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:06:59 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 19:44:49 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

int			fc_no_flags(char **av, t_fc *fc)
{
	if (av[1] && av[1][0] != '-')
	{
		fc->first = ft_strdup(av[1]);
		if (av[1] && av[2])
			fc->last = ft_strdup(av[2]);
	}
	if (av[1] && av[1][0] == '-' && ft_isnumbers(av[1] + 1))
	{
		fc->first = ft_strdup(av[1]);
		if (av[1] && av[2])
			fc->last = ft_strdup(av[2]);
	}
	if (fc->first || fc->last)
		return (1);
	else
		return (0);
}

int			fc_flags_e(char **av, t_fc *fc)
{
	if (ft_strequ(av[1], "-e"))
	{
		fc->flags[3] = 1;
		if (av[2])
			fc->editor = ft_strdup(av[2]);
		else
			return (fc_usage(-1, fc, 1));
		if (av[2] && av[3])
			fc->first = ft_strdup(av[3]);
		if (av[3] && av[4])
			fc->last = ft_strdup(av[4]);
		return (1);
	}
	return (0);
}

int			fc_flags_s(char **av, t_fc *fc)
{
	if (ft_strequ(av[1], "-s") == 1)
	{
		fc->flags[4] = 1;
		if (av[2])
		{
			if (ft_strstr(av[2], "=") || ft_strequ(av[2], "--"))
			{
				fc->pat_rep = ft_strdup(av[2]);
				if (!av[3])
					fc->first = ft_strdup("-1");
			}
			else
				fc->first = ft_strdup(av[2]);
		}
		else
			fc->first = ft_strdup("-1");
		if (!fc->first && av[2] && av[3])
			fc->first = ft_strdup(av[3]);
		return (1);
	}
	return (0);
}

int			fc_get_args(char **av, int argc, t_fc *fc)
{
	if (fc->flags[0] == 0 && (fc->flags[1] == 1 || fc->flags[2] == 1))
		return (fc_usage(-1, fc, 1));
	if (fc->flags[0] == 1)
	{
		if (av[argc])
			fc->first = ft_strdup(av[argc]);
		if (av[argc] && av[argc + 1])
			fc->last = ft_strdup(av[argc + 1]);
		return (1);
	}
	else
	{
		if (av[argc])
			fc->cmd = ft_strdup(av[argc]);
		return (1);
	}
	return (0);
}

int			fc_flags_lnr(char **av, t_fc *fc)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (av[i] && av[i][0] == '-' && av[i][1])
	{
		while (av[i][j])
		{
			if (av[i][1] >= '0' && av[i][1] <= '9')
				return (fc_get_args(av, i, fc));
			else if (av[i][j] == 'l')
				fc->flags[0] = 1;
			else if (av[i][j] == 'n')
				fc->flags[1] = 1;
			else if (av[i][j] == 'r')
				fc->flags[2] = 1;
			else
				return (fc_usage(-1, fc, 1));
			j++;
		}
		j = 1;
		i++;
	}
	return (fc_get_args(av, i, fc));
}
