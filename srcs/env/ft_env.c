/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:08:30 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/31 02:16:33 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

void	*ft_free_env(void)
{
	free_splitted(g_env->names);
	free_splitted(g_env->values);
	free_splitted(g_env->paths);
	free(g_env);
	return (NULL);
}

static int	ft_fill_paths(void)
{
	char	*path_val;

	path_val = ft_getvar("PATH");
	g_env->paths = ft_split(path_val, ':');
	if (g_env->paths)
		return (1);
	ft_free_env();
	return (0);
}

static int	ft_fill_env(char **ev)
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
		tmp = ft_strs_append_str(g_env->names, name);
		free(name);
		if (!tmp)
			return (ft_free_env() != NULL);
		g_env->names = tmp;
		tmp = ft_strs_append_str(g_env->values, value);
		free(value);
		if (!tmp)
			return (ft_free_env() != NULL);
		g_env->values = tmp;
	}
	return (ft_fill_paths());
}

t_env	*ft_init_env(char **ev)
{
	g_env = ft_calloc(1, sizeof(t_env));
	if (!g_env)
		return (NULL);
	g_env->names = ft_calloc(1, sizeof(char *));
	g_env->values = ft_calloc(1, sizeof(char *));
	g_env->paths = NULL;
	if (!g_env->names || !g_env->values)
	{
		free(g_env->values);
		free(g_env->names);
		free(g_env->paths);
		free(g_env);
		return (NULL);
	}
	if (!ft_fill_env(ev))
		return (NULL);
	return (g_env);
}
