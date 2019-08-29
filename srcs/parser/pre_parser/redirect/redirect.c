/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:00:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 03:02:26 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_default(t_redir **redir_info)
{
	t_redir	*ptr;
	t_type	t;

	ptr = *redir_info;
	t = ptr->type;
	if (t == GREAT || t == DGREAT || t == GREATAMPHYPH
		|| t == LESSAMPHYPH)
	{
		ptr->src_fd[0] = ft_strdup("1");
		ptr->src_fd[1] = 0;
	}
	else if (t == GREATAMP || t == AMPGREAT)
	{
		ptr->src_fd[0] = ft_strdup("1");
		ptr->src_fd[1] = ft_strdup("2");
		ptr->src_fd[2] = 0;
	}
	else if (t == LESS || t == LESSAMP || t == DLESS)
	{
		ptr->src_fd[0] = ft_strdup("0");
		ptr->src_fd[1] = 0;
	}
}

int		handle_needed_redir(t_lex **command_node, t_lex **redir_node)
{
	int		ret;

	ret = 0;
	if ((*redir_node)->token->type == GREAT)
		ret = handle_great(command_node);
	else if ((*redir_node)->token->type == GREATAMP)
		ret = handle_great_and(command_node);
	else if ((*redir_node)->token->type == AMPGREAT)
		ret = handle_and_great(command_node);
	else if ((*redir_node)->token->type == DGREAT)
		ret = handle_append(command_node);
	else if ((*redir_node)->token->type == LESS)
		ret = handle_less(command_node);
	else if ((*redir_node)->token->type == LESSAMP)
		ret = handle_less_and(command_node);
	else if ((*redir_node)->token->type == DLESS)
		ret = handle_heredoc(command_node);
	else if ((*redir_node)->token->type == GREATAMPHYPH)
		ret = handle_great_hyph(command_node);
	else if ((*redir_node)->token->type == LESSAMPHYPH)
		ret = handle_less_hyph(command_node);
	return (ret);
}

int		manage_cycle_redirect(t_lex *ptr, t_token *tok)
{
	t_lex	*start;

	start = ptr;
	while (ptr)
	{
		if (is_a_redirect(ptr->token->type))
		{
			if (handle_needed_redir(&start, &ptr))
			{
				clean_inside_token(&tok);
				return (1);
			}
			ptr = start;
		}
		else
			ptr = ptr->next;
	}
	clean_inside_token(&tok);
	return (0);
}

int		cycle_redirect(t_lex **command_node)
{
	t_lex	*ptr;
	t_token	*tok;
	t_lex	*node;

	tok = create_token("DELIM", DELIM);
	node = new_node(&tok);
	(*command_node)->token->command->prev = node;
	node->next = (*command_node)->token->command;
	(*command_node)->token->command = node;
	ptr = (*command_node)->token->command;
	return (manage_cycle_redirect(ptr, tok));
}

int		handle_redir(t_lex **lex)
{
	t_lex	*ptr;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type == CMD)
		{
			if (cycle_redirect(&ptr))
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
