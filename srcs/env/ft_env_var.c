/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 08:06:34 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:41:51 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

static int	ft_update_paths(char *val)
{
	free_splitted(g_env->paths);
	g_env->paths = ft_split(val, ':');
	if (g_env->paths)
		return (1);
	ft_free_env();
	return (0);
}

int			ft_modify_var(char *name, char *value)
{
	char	**found;
	size_t	index;

	found = ft_find_str(g_env->names, name);
	if (!found)
		return (0);
	index = found - g_env->names;
	free(g_env->values[index]);
	g_env->values[index] = value;
	free(name);
	if (!ft_strcmp(name, "PATH"))
		return (ft_update_paths(value));
	return (1);
}

int			ft_add_var(char *var)
{
	char	*name;
	char	*value;
	char	**splitted_var;
	char	**tmp;

	splitted_var = ft_split(var, '=');
	name = ft_strdup(splitted_var[0]);
	value = ft_strjoin_arr(splitted_var + 1, '=');
	free_splitted(splitted_var);
	if (ft_getvar(name))
		return (ft_modify_var(name, value));
	tmp = ft_strs_append_str(g_env->names, name);
	if (!ft_strcmp(name, "PATH") && !ft_update_paths(value))
		return (ft_free_env() != NULL);
	free(name);
	if (!tmp)
		return (ft_free_env() != NULL);
	g_env->names = tmp;
	tmp = ft_strs_append_str(g_env->values, value);
	free(value);
	if (!tmp)
		return (ft_free_env() != NULL);
	g_env->values = tmp;
	return (1);
}

int			ft_delete_var(char *name)
{
	char	**found;
	char	**tmp;
	size_t	index;

	found = ft_find_str(g_env->names, name);
	if (!found)
		return (0);
	index = found - g_env->names;
	tmp = ft_strs_remove(g_env->names, index);
	if (!tmp)
		return (ft_free_env() != NULL);
	g_env->names = tmp;
	tmp = ft_strs_remove(g_env->values, index);
	if (!tmp)
		return (ft_free_env() != NULL);
	g_env->values = tmp;
	if (!ft_strcmp(name, "PATH"))
	{
		free_splitted(g_env->paths);
		g_env->paths = NULL;
	}
	return (1);
}
