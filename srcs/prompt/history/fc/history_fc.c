/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:29:16 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/25 19:48:51 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

void		init_fc(t_fc *fc)
{
	fc->editor = NULL;
	fc->first = NULL;
	fc->last = NULL;
	fc->first_index = 0;
	fc->last_index = 0;
	fc->pat_rep = NULL;
	fc->cmd = NULL;
}

int			fc_flags(char **av, t_fc *fc)
{
	int		ret;

	ret = 0;
	if ((ret = fc_no_flags(av, fc)))
		if (ret < 0 || ret > 0)
			return (ret);
	if ((ret = fc_flags_e(av, fc)))
		if (ret < 0 || ret > 0)
			return (ret);
	if ((ret = fc_flags_s(av, fc)))
		if (ret < 0 || ret > 0)
			return (ret);
	if ((ret = fc_flags_lnr(av, fc)))
		if (ret < 0 || ret > 0)
			return (ret);
	return (0);
}

int			fc_exec(t_fc *fc, t_pos *pos)
{
	if (FC_L)
		if (fc_l(fc, pos) == -1)
			return (-1);
	if (FC_E || FC_NO_FLAGS)
		if (fc_e(fc, pos) == -1)
			return (-1);
	if (FC_S)
		if (fc_s(fc, pos) == -1)
			return (-1);
	return (1);
}

void		fc_free(t_fc *fc)
{
	ft_strdel(&fc->pat_rep);
	ft_strdel(&fc->first);
	ft_strdel(&fc->last);
	ft_strdel(&fc->editor);
	ft_strdel(&fc->cmd);
}

int			builtin_fc(char **av, t_pos *pos)
{
	t_fc	fc;
	int		i;

	i = 0;
	while (i < 5)
		fc.flags[i++] = 0;
	init_fc(&fc);
	if (fc_flags(av, &fc) == -1)
		return (-2);
	fc_filter_history(&fc, pos);
	if (fc_exec(&fc, pos) == -1)
		return (-2);
	fc_free(&fc);
	return (0);
}
