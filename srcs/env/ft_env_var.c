/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 08:06:34 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 09:33:45 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

static int	ft_update_paths(t_env *env, char *val)
{
	free_splitted(env->paths);
	env->paths = ft_split(val, ':');
	if (env->paths)
		return (1);
	ft_free_env(env);
	return (0);
}

int	ft_modify_var(t_env *env, char *name, char *value)
{
	char	**found;
	size_t	index;

	found = ft_find_str(env->names, name);
	if (!found)
		return (0);
	index = found - env->names;
	free(env->values[index]);
	env->values[index] = value;
	free(name);
	if (!ft_strcmp(name, "PATH"))
		return (ft_update_paths(env, value));
	return (1);
}

int	ft_add_var(t_env *env, char *var)
{
	char	*name;
	char	*value;
	char	**splitted_var;
	char	**tmp;

	splitted_var = ft_split(var, '=');
	name = ft_strdup(splitted_var[0]);
	value = ft_strjoin_arr(splitted_var + 1, '=');
	free_splitted(splitted_var);
	if (ft_getvar(env, name))
		return (ft_modify_var(env, name, value));
	tmp = ft_strs_append_str(env->names, name);
	if (!ft_strcmp(name, "PATH") && !ft_update_paths(env, value))
		return (ft_free_env(env) != NULL);
	free(name);
	if (!tmp)
		return (ft_free_env(env) != NULL);
	env->names = tmp;
	tmp = ft_strs_append_str(env->values, value);
	free(value);
	if (!tmp)
		return (ft_free_env(env) != NULL);
	env->values = tmp;
	return (1);
}

int	ft_delete_var(t_env *env, char *name)
{
	char	**found;
	char	**tmp;
	size_t	index;

	found = ft_find_str(env->names, name);
	if (!found)
		return (0);
	index = found - env->names;
	tmp = ft_strs_remove(env->names, index);
	if (!tmp)
		return (ft_free_env(env) != NULL);
	env->names = tmp;
	tmp = ft_strs_remove(env->values, index);
	if (!tmp)
		return (ft_free_env(env) != NULL);
	env->values = tmp;
	if (!ft_strcmp(name, "PATH"))
	{
		free_splitted(env->paths);
		env->paths = NULL;
	}
	return (1);
}
