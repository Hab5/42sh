/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 18:50:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

char	*assembly_cmd_process(t_process *p)
{
	char	*str;
	char	*tmp;
	char	*cache;
	int		i;

	i = -1;
	str = ft_strdup(p->cmd[++i]);
	while (p->cmd[++i])
	{
		tmp = ft_strjoin(str, " ");
		cache = ft_strjoin(tmp, p->cmd[i]);
		ft_strdel(&str);
		ft_strdel(&tmp);
		str = cache;
	}
	cache = ft_strjoin(str, " ");
	ft_strdel(&str);
	if (p->final_str)
		str = ft_strjoin(cache, p->final_str);
	else
		str = ft_strjoin(cache, "");
	ft_strdel(&cache);
	return (str);
}

void	assembly_command_s(t_process *p, char **str)
{
	char		*tmp;
	char		*cache;

	if (!(*str))
		(*str) = assembly_cmd_process(p);
	else
	{
		tmp = assembly_cmd_process(p);
		cache = ft_strjoin(*str, tmp);
		ft_strdel(str);
		ft_strdel(&tmp);
		(*str) = cache;
	}
	if (p->next)
	{
		cache = ft_strjoin(*str, " | ");
		ft_strdel(str);
		(*str) = cache;
	}
}
