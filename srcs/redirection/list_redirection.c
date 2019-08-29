/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:23:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/17 14:02:50 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_redirection	*init_redirection(void)
{
	t_redirection	*r;

	if (!(r = (t_redirection*)malloc(sizeof(t_redirection) * 1)))
		return (NULL);
	r->in = STDIN_FILENO;
	r->out = STDOUT_FILENO;
	r->error = STDERR_FILENO;
	r->redirect = ft_init_redirect();
	return (r);
}

t_redirection	*base_redirection(void)
{
	t_redirection	*r;

	if (!(r = (t_redirection*)malloc(sizeof(t_redirection) * 1)))
		return (NULL);
	r->in = STDIN_FILENO;
	r->out = STDOUT_FILENO;
	r->error = STDERR_FILENO;
	r->redirect = NULL;
	return (r);
}
