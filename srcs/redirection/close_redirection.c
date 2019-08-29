/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/28 13:22:31 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

int			close_file_command(t_lex *lex, t_redirection **r)
{
	t_lex	*head;

	head = lex;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir
			&& lex->redir->dest_fd
			&& ft_atoi(lex->redir->dest_fd) != -1)
			if (lex->redir->filename || lex->redir->close == 1)
				if (verif_close(ft_atoi(lex->redir->dest_fd)))
					close(ft_atoi(lex->redir->dest_fd));
		lex = lex->next;
	}
	lex = head;
	delete_redirection(&(*r));
	return (0);
}

static int	file_to_close_bis(t_token *t, t_job *j)
{
	t_lex	*lex;
	int		i;

	lex = t->command;
	if (!(j->close_fd = (int*)malloc(sizeof(int) * (j->len_close + 1))))
		return (-1);
	i = -1;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir &&
				lex->redir->dest_fd &&
				ft_atoi(lex->redir->dest_fd) != -1)
			if (lex->redir->filename || lex->redir->close == 1)
				j->close_fd[++i] = ft_atoi(lex->redir->dest_fd);
		lex = lex->next;
	}
	return (0);
}

int			file_to_close(t_token *t, t_job *j)
{
	t_lex	*lex;
	int		verif;

	if (!t)
		return (-1);
	lex = t->command;
	while (lex)
	{
		if (lex->token->type == REDIR && lex->redir &&
				lex->redir->dest_fd &&
				ft_atoi(lex->redir->dest_fd) != -1)
			if (lex->redir->filename || lex->redir->close == 1)
				j->len_close++;
		lex = lex->next;
	}
	verif = file_to_close_bis(t, j);
	return (verif);
}
