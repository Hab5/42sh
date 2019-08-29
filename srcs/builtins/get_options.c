/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:17:29 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/25 19:42:03 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			g_optind = 1;
int			g_opterr = 1;
int			g_optopt = 0;
int			g_optreset = 0;
char		*g_optarg = NULL;

void		ft_getopt_reset(void)
{
	g_optind = 1;
	g_optreset = 1;
}

static int	ft_getopt_error(char *const *av, const char *optstr, int err)
{
	if (g_opterr == 1 && err == 1)
		ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n", av[0],
					g_optopt);
	else if (g_opterr == 1 && err == 2)
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- %c\n",
					av[0], g_optopt);
	if (optstr[0] == ':')
		return (':');
	return ('?');
}

static int	ft_optgetarg(int ac, char *const *av, const char *optstr, int i)
{
	char	*c;

	c = ft_strchr((char *)optstr, g_optopt);
	++c;
	if (*c == ':')
	{
		if (av[g_optind][i + 1] == '\0')
		{
			if ((g_optind + 1) >= ac || !av[g_optind + 1])
				return (ft_getopt_error(av, optstr, 2));
			g_optarg = (char *)av[g_optind + 1];
			g_optind += 2;
		}
		else
		{
			g_optarg = (char *)&(av[g_optind][i + 1]);
			++g_optind;
		}
		g_optreset = 1;
	}
	return (g_optopt);
}

static int	ft_optgetind(int ac, char *const *av, int nextchar)
{
	if (g_optind >= ac)
		return (-1);
	if (ft_strequ(av[g_optind], "-") || ft_strequ(av[g_optind], "--"))
	{
		if (ft_strequ(av[g_optind], "--"))
			++g_optind;
		return (-1);
	}
	if (av[g_optind][0] != '-')
		return (-1);
	if (av[g_optind][nextchar] == '\0')
	{
		++g_optind;
		return (ft_optgetind(ac, av, 1));
	}
	return (nextchar);
}

int			ft_getopt(int ac, char *const *av, const char *optstr)
{
	static int	nextchar = 1;
	int			i;

	if (g_optind >= ac || av[g_optind] == NULL || !optstr)
		return (-1);
	if (g_optreset == 1)
	{
		g_optreset = 0;
		nextchar = 1;
	}
	if ((i = ft_optgetind(ac, av, nextchar)) == -1)
		return (-1);
	nextchar = i + 1;
	if (ft_strchr_exist((char *)optstr, av[g_optind][i])
			&& av[g_optind][i] != ':')
	{
		g_optopt = av[g_optind][i];
		return (ft_optgetarg(ac, av, optstr, i));
	}
	else
	{
		g_optopt = av[g_optind][i];
		return (ft_getopt_error(av, optstr, 1));
	}
}
