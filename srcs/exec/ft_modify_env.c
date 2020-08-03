/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 12:48:41 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/27 13:03:55 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

static size_t	ft_strlen_cur(char *var)
{
	char	**splitted;
	size_t	len;

	splitted = ft_split(var, '=');
	len = ft_strlen(splitted[0]);
	free_splitted(splitted);
	return (len);
}

static int		ft_modify_var(t_env *env, char *name, char *value)
{
	char	**ev;
	char	*equal;

	ev = env->env;
	equal = ft_strjoin(name, "=");
	while (*ev)
	{
		if (ft_strlen(name) == ft_strlen_cur(*ev) && !(ft_strncmp(*ev, name, ft_strlen(name))))
		{
			free(*ev);
			*ev = ft_strjoin(equal, value);
			free(equal);
			if (!ft_strncmp(name, "PATH", ft_strlen(name)))
			{
				free_splitted(env->paths);
				init_paths(env);
			}
			return (1);
		}
		ev++;
	}
	free(equal);
	return (0);
}

void			ft_add_var(t_env *env, char *name, char *value)
{
	char	**ev;
	char	**saved;
	char	**new;
	char	*tmp;
	size_t	size;

	if (ft_modify_var(env, name, value))
		return ;
	ev = env->env;
	saved = ev;
	size = ft_sizeof(ev);
	if (!(env->env = (char **)ft_calloc(size + 2, sizeof(char *))))
		return ;
	new = env->env;
	while (*ev)
	{
		*new = ft_strdup(*ev);
		ev++;
		new++;
	}
	tmp = ft_strjoin(name, "=");
	*new = ft_strjoin(tmp, value);
	if (ft_strlen(name) == 4 && !ft_strncmp(name, "PATH", 4))
		init_paths(env);
	free(tmp);
	free_splitted(saved);
}

void			ft_delete_var(t_env *env, char *name)
{
	char	**ev;
	char	**saved;
	char	**new;

	ev = env->env;
	saved = ev;
	if (!(env->env = ft_calloc(ft_sizeof(env->env), sizeof(char *))))
		return ;
	new = env->env;
	while (*ev)
	{
		if (ft_strlen(name) == ft_strlen_cur(*ev) && !ft_strncmp(*ev, name, ft_strlen(name)))
		{
			ev++;
			continue ;
		}
		*new = ft_strdup(*ev);
		new++;
		ev++;
	}
	if (!ft_strncmp(name, "PATH", 4))
	{
		free_splitted(env->paths);
		env->paths = NULL;
	}
	free_splitted(saved);
}
