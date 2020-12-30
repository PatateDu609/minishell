/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:08:30 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 09:33:36 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

void	*ft_free_env(t_env *env)
{
	free_splitted(env->names);
	free_splitted(env->values);
	free_splitted(env->paths);
	free(env);
	return (NULL);
}

static int	ft_fill_paths(t_env *env)
{
	char	*path_val;

	path_val = ft_getvar(env, "PATH");
	env->paths = ft_split(path_val, ':');
	if (env->paths)
		return (1);
	ft_free_env(env);
	return (0);
}

static int	ft_fill_env(t_env *env, char **ev)
{
	char	**var;
	char	*value;
	char	*name;
	char	**tmp;

	while (*ev)
	{
		var = ft_split(*ev++, '=');
		name = ft_strdup(*var);
		value = ft_strjoin_arr(var + 1, '=');
		free_splitted(var);
		tmp = ft_strs_append_str(env->names, name);
		free(name);
		if (!tmp)
			return (ft_free_env(env) != NULL);
		env->names = tmp;
		tmp = ft_strs_append_str(env->values, value);
		free(value);
		if (!tmp)
			return (ft_free_env(env) != NULL);
		env->values = tmp;
	}
	return (ft_fill_paths(env));
}

t_env	*ft_init_env(char **ev)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->names = ft_calloc(1, sizeof(char *));
	env->values = ft_calloc(1, sizeof(char *));
	env->paths = NULL;
	if (!env->names || !env->values)
	{
		free(env->values);
		free(env->names);
		free(env->paths);
		free(env);
		return (NULL);
	}
	if (!ft_fill_env(env, ev))
		return (NULL);
	return (env);
}
