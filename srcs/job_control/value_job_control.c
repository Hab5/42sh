/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_job_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:54:45 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:45:24 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "builtins.h"

char		value_char_job(int current, int max)
{
	if (current == max)
		return ('+');
	if (current == max - 1)
		return ('-');
	return (' ');
}
