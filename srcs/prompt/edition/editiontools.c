/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editiontools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:17:31 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/26 05:01:35 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "env.h"

void		free_arr(char **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		ft_strdel(&cmd[i]);
	free(cmd);
	cmd = NULL;
}

void		prompt_mod(char **promptpath, int i, char cwd[])
{
	ft_putstr("\033[1;32m");
	if (i > 2)
	{
		ft_putstr("[");
		ft_putstr(promptpath[i - 2]);
		ft_putstr("/");
		ft_putstr(promptpath[i - 1]);
		ft_putstr("]");
		ft_putstr(" » ");
	}
	else
	{
		ft_putstr("[");
		ft_putstr(cwd);
		ft_putstr("]");
		ft_putstr(" » ");
	}
	ft_putstr("\033[0m");
}

void		print_prompt(void)
{
	char	cwd[1024];
	char	**promptpath;
	int		i;

	ft_bzero(cwd, 1024);
	getcwd(cwd, 1023);
	promptpath = ft_strsplit(cwd, '/');
	if ((!promptpath) || cwd[0] == '\0')
	{
		ft_putstr("\033[1;32m[/] » \033[0m");
		return ;
	}
	i = 0;
	while (promptpath[i])
		i++;
	prompt_mod(promptpath, i, cwd);
	free_arr(promptpath);
}

void		get_inputlen(t_pos *pos, t_node *input)
{
	t_node	*current;
	int		i;

	i = 0;
	current = input;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	pos->inputlen = i - 1;
}

void		check_scrolling(t_pos *pos)
{
	if (pos->row == pos->termsize.ws_row)
	{
		savecursor(pos);
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->termsize.ws_row), 1, ft_outc);
		ft_putstr(tgetstr("sf", NULL));
		cursorback(pos);
	}
}
