/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 09:05:19 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 21:02:26 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_ht_hash	*g_alias_table;

char				*alias_rep_word(char *base, int *isrep,
									t_repalias *cur_alias)
{
	char		*val;
	t_repalias	*curr;
	char		*new;

	if (!base)
		return (base);
	val = ht_hash_search(g_alias_table, base);
	if (val == NULL)
		return (base);
	curr = cur_alias;
	while (curr != NULL)
	{
		if (ft_strequ(base, curr->key))
			return (base);
		curr = curr->next;
	}
	*isrep = 1;
	if (!(new = ft_strdup(val)))
		return (NULL);
	if (*new == '\0')
		return (new);
	cur_alias = alias_rep_addalias(cur_alias, base, val);
	new = alias_replace(new, cur_alias);
	cur_alias = alias_rep_delalias(cur_alias);
	return (new);
}

void				alias_rep_cmd(t_lex **lex, t_repalias *cur_alias, char *bn)
{
	t_lex	*ptr;
	int		isrep;

	ptr = *lex;
	isrep = 0;
	while (ptr)
	{
		if (ptr->token->type == WORD || ptr->token->type == NUMBER)
		{
			removebackslash(&(ptr->token->data));
			bn = ptr->token->data;
			if (!(ptr->token->data = alias_rep_word(ptr->token->data,
														&isrep, cur_alias)))
			{
				ft_strdel(&bn);
				return ;
			}
			if (isrep != 0)
				ft_strdel(&bn);
			if (ptr->token->data[0] != '\0')
				return ;
			isrep = 0;
		}
		ptr = ptr->next;
	}
}

void				alias_rep_recursive(t_lex **lex, t_repalias *cur_alias)
{
	t_lex	*ptr;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type == CMD)
			alias_rep_cmd(&ptr->token->command, cur_alias, NULL);
		ptr = ptr->next;
	}
}

char				*alias_rep_redo_input(t_lex **lex, char *new)
{
	t_lex	*ptr;
	char	*bin;

	ptr = *lex;
	while (ptr)
	{
		if (ptr->token->type != CMD && ptr->token->type != DELIM
			&& ptr->token->type != NUL)
		{
			bin = new;
			new = ft_strjoin(new, ptr->token->data);
			ft_strdel(&bin);
			if (new == NULL)
				return (NULL);
		}
		if (ptr->token->type == CMD)
		{
			if (!(new = alias_rep_redo_input(&ptr->token->command, new)))
				return (NULL);
		}
		ptr = ptr->next;
	}
	return (new);
}

char				*alias_replace(char *input, t_repalias *cur_alias)
{
	t_lex	*lex;
	char	*new_input;

	if (!input)
		return (input);
	lex = NULL;
	reading_input(input, &lex);
	lex = add_delim(&lex);
	handle_quotes(&lex);
	simple_command(&lex);
	alias_handle_redir(&lex, NULL);
	alias_rep_recursive(&lex, cur_alias);
	ft_strdel(&input);
	if ((new_input = ft_strnew(1)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "42sh: malloc error\n");
		clean_lex(&lex);
		return (NULL);
	}
	new_input = alias_rep_redo_input(&lex, new_input);
	clean_lex(&lex);
	return (new_input);
}
