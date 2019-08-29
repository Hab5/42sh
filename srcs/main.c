/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:01:09 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 20:28:04 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "job.h"
#include "builtins.h"

t_ht_hash	*g_hash_table;
t_ht_hash	*g_alias_table;

void		flags(int argc, char **argv)
{
	g_print_ast = 0;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "--ast") == 0)
			g_print_ast = 1;
		if (ft_strcmp(argv[1], "-a") == 0)
			g_print_ast = 1;
	}
	return ;
}

static void	edit_shell(char *name_exec)
{
	int	in;
	int	out;
	int	error;

	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0
		|| isatty(STDERR_FILENO) == 0)
		exit(1);
	in = open(ttyname(STDIN_FILENO), O_WRONLY);
	out = open(ttyname(STDOUT_FILENO), O_WRONLY);
	error = open(ttyname(STDERR_FILENO), O_WRONLY);
	if ((dup2(STDIN_FILENO, in)) == -1)
		exit(1);
	if ((dup2(STDOUT_FILENO, out)) == -1)
		exit(1);
	if ((dup2(STDERR_FILENO, out)) == -1)
		exit(1);
	cpy_std(in, out, error);
	ft_name_exec(name_exec);
}

void		run(char *input, t_pos *pos)
{
	t_lex	*lex;
	t_ast	*ast;
	int		verif;

	lex = NULL;
	ast = NULL;
	input = alias_replace(input, NULL);
	verif = check_whitespace_input(input);
	if (verif && (lex = lexer(input)))
		if ((ast = ast_parser(lex)) && (solo_tree(ast, pos) < 0))
			interpreter(ast, pos, 0);
	if (input)
	{
		ft_strdel(&input);
		clean_lex(&lex);
		clean_ast(ast);
	}
}

int			main(int argc, char **argv, char **environ)
{
	t_multi	*multi_input;
	char	*input;
	t_pos	pos;

	input = NULL;
	multi_input = NULL;
	edit_shell(argv[0]);
	welcome();
	flags(argc, argv);
	init_prompt(&pos);
	init_alias();
	while (21)
	{
		if (argc && argv && environ)
			if ((input = prompt(multi_input, &pos)))
				run(input, &pos);
		job_notif();
		manage_id_job(0);
	}
	return (0);
}
