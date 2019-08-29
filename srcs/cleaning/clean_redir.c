/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <aleduc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 01:23:34 by aleduc            #+#    #+#             */
/*   Updated: 2019/05/07 20:32:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_redir(t_redir **redir)
{
	if ((!redir) || (!(*redir)))
		return ;
	if ((*redir)->src_fd)
		ft_arraydel(&((*redir)->src_fd));
	ft_strdel(&((*redir)->dest_fd));
	ft_strdel(&((*redir)->filename));
	ft_strdel(&((*redir)->heredoc));
	free(*redir);
	(*redir) = NULL;
}
