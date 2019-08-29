/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 08:07:54 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 08:31:39 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

extern t_ht_hash	*g_hash_table;
extern t_ht_hash	*g_alias_table;

int					siginthandler(int signum)
{
	(void)signum;
	ft_printf("signal handler\n");
	return (0);
}

void				cpy_std(int in, int out, int error)
{
	char	*s_in;
	char	*s_out;
	char	*s_error;

	s_in = ft_itoa(in);
	s_out = ft_itoa(out);
	s_error = ft_itoa(error);
	add_set_value_perm("STDIN", s_in, 3);
	add_set_value_perm("STDOUT", s_out, 3);
	add_set_value_perm("STDERR", s_error, 3);
	ft_strdel(&s_in);
	ft_strdel(&s_out);
	ft_strdel(&s_error);
}

int					check_whitespace_input(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void				ft_name_exec(char *name_exec)
{
	int		len;
	char	*cache;

	len = ft_strlen(name_exec);
	if (len < 3)
		return ;
	cache = ft_strsub(name_exec, 2, len);
	add_set_value("0", cache);
	add_set_value("EDITOR", "vim");
	add_set_value("FCEDIT", "vim");
	ft_strdel(&cache);
}

void				init_alias(void)
{
	g_hash_table = ht_hash_new();
	g_alias_table = ht_hash_new();
	if (OS == 0)
		ht_hash_insert(g_alias_table, "ls", "ls -G");
	else
	{
		free_maillon_env("LS_COLORS", 0);
		ht_hash_insert(g_alias_table, "ls", "ls --color");
	}
	ht_hash_insert(g_alias_table, "b", "base64 /dev/urandom");
	ht_hash_insert(g_alias_table, "..", "cd ..");
	ht_hash_insert(g_alias_table, "-", "cd -");
	ht_hash_insert(g_alias_table, "?", "echo $?");
	ht_hash_insert(g_alias_table, "posix", "bash --posix");
}
