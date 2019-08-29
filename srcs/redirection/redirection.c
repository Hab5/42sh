/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:50:50 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 21:46:32 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "job.h"

void		standard_redirection(t_redirection *r)
{
	if (r->in != STDIN_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDIN_FILENO) == 0)
	{
		if (dup2(r->in, STDIN_FILENO) == -1)
			exit(-1);
		if (verif_close(r->in))
			close(r->in);
	}
	if (r->out != STDOUT_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDOUT_FILENO) == 0)
	{
		if (dup2(r->out, STDOUT_FILENO) == -1)
			exit(-1);
		if (verif_close(r->out))
			close(r->out);
	}
	if (r->error != STDERR_FILENO
		&& ft_fd_redirect_exist(r->redirect, STDERR_FILENO) == 0)
	{
		if (dup2(r->error, STDERR_FILENO) == -1)
			exit(-1);
		if (verif_close(r->error))
			close(r->error);
	}
}

static void	custom_redirection(t_redirect *lst)
{
	if (lst->base != -1)
	{
		if (lst->type == DGREAT)
		{
			lst->new_fd = get_end_line(lst->name_file);
			ft_strdel(&lst->name_file);
		}
		else if (lst->type == AMPGREAT && lst->base == STDERR_FILENO)
			lst->new_fd = STDOUT_FILENO;
		else
		{
			if (lst->name_file)
				lst->new_fd = open(lst->name_file, O_RDWR);
		}
		if (lst->type == LESSAMPHYPH)
			close(lst->base);
		else if (lst->type == GREATAMPHYPH)
			close(lst->base);
		else
			other_redir(lst);
	}
}

static int	check_new_fd(t_redirect *head, t_redirect *test,
		t_redirect *redirect, int verif)
{
	if (fcntl(redirect->new_fd, F_GETFD) == -1
			&& (redirect->type == GREATAMP
			|| redirect->type == LESSAMP) && redirect != head)
	{
		while (test && (!(test->base == redirect->base
			&& test->new_fd == redirect->new_fd
			&& test->type == redirect->type)))
		{
			if (test->base == redirect->new_fd
				|| test->new_fd == redirect->new_fd)
				verif = 1;
			test = test->next;
		}
		if (verif == 0)
			return (-1);
	}
	return (verif);
}

static int	check_fd_is_good(t_redirection *r)
{
	t_redirect	*redirect;
	t_redirect	*head;
	t_redirect	*test;
	t_redirect	*sup;
	int			verif;

	redirect = r->redirect;
	head = r->redirect;
	sup = r->redirect;
	while (redirect && redirect->base != -1)
	{
		test = head;
		verif = 0;
		verif = check_new_fd(head, test, redirect, verif);
		if (verif == -1)
			return (-1);
		if (fcntl(redirect->new_fd, F_GETFD) == -1
			&& (redirect->type == GREATAMP
			|| redirect->type == LESSAMP) && redirect == head)
			return (-1);
		redirect = redirect->next;
	}
	r->redirect = sup;
	return (0);
}

void		redirection_fd(t_redirection *r)
{
	t_redirect	*lst;

	if (!r)
		return ;
	if (check_fd_is_good(r) == -1)
	{
		display_bad_file_descriptor(STDERR_FILENO);
		execve_bin_test();
		exit(-1);
	}
	lst = r->redirect;
	while (lst)
	{
		custom_redirection(lst);
		lst = lst->next;
	}
	lst = r->redirect;
	redirection_fd_bis(r);
	r->redirect = lst;
}
