/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:54:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 08:11:57 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

static int	count_env(int env)
{
	t_env	*my_env;
	t_env	*head;
	int		len;

	len = 0;
	my_env = get_env(0, NULL);
	head = my_env;
	while (my_env->next)
	{
		if (env == 0 || (env == 1 && my_env->see_env == 1))
			len++;
		my_env = my_env->next;
	}
	my_env = head;
	return (len);
}

char		**create_list_env(t_env *my_env, int env)
{
	char	*str;
	t_env	*head;
	char	**dst;
	int		len;

	head = my_env;
	len = count_env(env);
	my_env = head;
	if (!(dst = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	len = -1;
	while (my_env->next)
	{
		if (env == 0 || (env == 1 && my_env->see_env == 1))
		{
			str = ft_strjoin(my_env->key, "=");
			dst[++len] = ft_strjoin(str, my_env->value ? my_env->value : "");
			ft_strdel(&str);
		}
		my_env = my_env->next;
	}
	dst[++len] = NULL;
	my_env = head;
	return (dst);
}

int			edit_setenv(char *key, char *value)
{
	int	verif;

	if (!value)
		value = "";
	verif = add_set_value(key, value);
	if (verif != -1)
		verif = edit_export(key);
	return (verif);
}

int			ft_unset_key(char *key, t_env *my_env)
{
	int	verif;

	verif = 0;
	while (my_env->next)
	{
		if (ft_strequ(my_env->key, key))
		{
			my_env->see_env = 0;
			verif = 1;
			break ;
		}
		my_env = my_env->next;
	}
	return (verif);
}

int			ft_unsetenv(char **key)
{
	int		i;
	int		verif;
	t_env	*my_env;

	my_env = get_env(0, NULL);
	i = 0;
	while (key[++i])
		verif = ft_unset_key(key[i], my_env);
	return (verif);
}
