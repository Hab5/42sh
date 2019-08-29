/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:48:23 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/27 17:03:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env		*init_maillon_env(void)
{
	t_env	*lst;

	if (!(lst = (t_env*)malloc(sizeof(t_env) * 1)))
		return (NULL);
	lst->key = NULL;
	lst->value = NULL;
	lst->see_env = 0;
	lst->next = NULL;
	return (lst);
}

void		init_variable(void)
{
	int		shlvl;
	char	*s_shlvl;

	add_set_value("?", "0");
	add_set_value("0", "42sh");
	add_set_value("-", "a");
	add_set_value("#", "0");
	s_shlvl = value_line_path("SHLVL", 0);
	if (!s_shlvl)
		s_shlvl = ft_strdup("-1");
	shlvl = ft_atoi(s_shlvl) + 1;
	ft_strdel(&s_shlvl);
	s_shlvl = ft_itoa(shlvl);
	add_set_value("SHLVL", s_shlvl);
	ft_strdel(&s_shlvl);
}

t_env		*init_env(void)
{
	int			i;
	char		**split;
	t_env		*head;
	t_env		*current;
	extern char	**environ;

	i = -1;
	current = init_maillon_env();
	head = current;
	if (!environ)
		return (NULL);
	while (environ[++i])
	{
		split = ft_strsplit(environ[i], '=');
		current->key = ft_strdup(split[0]);
		current->value = ft_strdup(split[1] ? split[1] : "");
		current->see_env = 1;
		ft_arraydel(&split);
		current->next = init_maillon_env();
		current = current->next;
	}
	return (head);
}

t_env		*ft_cpy_env(void)
{
	t_env	*my_env;
	t_env	*dst;
	t_env	*h;

	my_env = get_env(0, NULL);
	dst = init_maillon_env();
	h = dst;
	if (!my_env)
		return (h);
	while (my_env->next)
	{
		dst->key = ft_strdup(my_env->key);
		dst->value = ft_strdup(my_env->value);
		dst->see_env = my_env->see_env;
		dst->next = init_maillon_env();
		dst = dst->next;
		my_env = my_env->next;
	}
	return (h);
}
