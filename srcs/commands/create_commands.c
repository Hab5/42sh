/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 11:33:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 18:11:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

char		*type_redir(t_type type)
{
	char	*result;

	if (type == LESS)
		result = ft_strdup("<");
	else if (type == DLESS)
		result = ft_strdup("<<");
	else if (type == GREAT)
		result = ft_strdup(">");
	else if (type == DGREAT)
		result = ft_strdup(">>");
	else if (type == AMPGREAT)
		result = ft_strdup("&>");
	else if (type == GREATAMP)
		result = ft_strdup(">&");
	else if (type == LESSAMP)
		result = ft_strdup("<&");
	else if (type == LESSAMPHYPH)
		result = ft_strdup("<&-");
	else if (type == GREATAMPHYPH)
		result = ft_strdup(">&");
	else
		result = NULL;
	return (result);
}

char		*construct_str_redir(t_redir *redir, char *type)
{
	char	*final;

	if (redir->type != AMPGREAT)
		final = ft_strjoin(redir->src_fd[0], type);
	else
		final = ft_strjoin("", type);
	return (final);
}

char		*construct_dst_redir(t_redir *redir, char *final)
{
	char	*cache;

	if (redir->type == DLESS)
		cache = ft_strjoin(final, redir->heredoc);
	else if (redir->filename)
		cache = ft_strjoin(final, redir->filename);
	else if (redir->type == LESSAMPHYPH || redir->type == GREATAMPHYPH)
		cache = ft_strjoin(final, "");
	else
		cache = ft_strjoin(final, redir->dest_fd);
	return (cache);
}

void		construct_redir(t_redir *redir, char **str)
{
	char	*final;
	char	*cache;
	char	*type;

	type = type_redir(redir->type);
	final = construct_str_redir(redir, type);
	cache = construct_dst_redir(redir, final);
	ft_strdel(&type);
	ft_strdel(&final);
	if (*str)
	{
		final = ft_strjoin(*str, cache);
		ft_strdel(str);
		ft_strdel(&cache);
		(*str) = final;
	}
	else
		(*str) = cache;
}

char		*ft_construct_redirection(t_token *token)
{
	t_lex	*lex;
	char	*str;
	char	*tmp;

	lex = token->command;
	str = NULL;
	while (lex)
	{
		if (lex->redir)
			construct_redir(lex->redir, &str);
		if (str)
		{
			tmp = ft_strjoin(str, " ");
			ft_strdel(&str);
			str = tmp;
		}
		lex = lex->next;
	}
	if (!str)
		str = ft_strdup("");
	return (str);
}
