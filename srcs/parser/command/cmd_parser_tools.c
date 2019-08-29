/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 07:46:31 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 07:52:12 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "sh21.h"
#include "env.h"

int				check_last(void)
{
	int			check;
	char		*str;

	str = value_line_path("?", 0);
	check = ft_atoi(str);
	ft_strdel(&str);
	return (check);
}
