/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:08:30 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/08 13:50:06 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"
#include "ft_parser.h"

void		*ft_free_env(void)
{
	free_splitted(g_env->names);
	free_splitted(g_env->values);
	free_splitted(g_env->paths);
	free_splitted(g_env->merged);
	free(g_env);
	return (NULL);
}

static void	ft_update_shlvl(void)
{
	int		val;
	char	*shlvl;
	char	*tmp;
	char	*parts[3];

	shlvl = ft_getvar("SHLVL");
	if (!shlvl)
		val = 1;
	else
		val = ft_atoi(shlvl) + 1;
	if (val < 0)
		val = 0;
	shlvl = ft_itoa(val);
	parts[0] = "SHLVL";
	parts[1] = shlvl;
	parts[2] = NULL;
	tmp = shlvl;
	shlvl = ft_strjoin_arr(parts, '=');
	ft_add_var(shlvl);
	free(tmp);
	free(shlvl);
}

static int	ft_fill_paths(void)
{
	char	*path_val;
	char	*def;

	path_val = ft_getvar("PATH");
	def = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (!path_val)
		return (ft_add_var(def));
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

t_env		*ft_init_env(char **ev)
{
	g_env = ft_calloc(1, sizeof(t_env));
	if (!g_env)
		return (NULL);
	g_env->names = ft_calloc(1, sizeof(char *));
	g_env->values = ft_calloc(1, sizeof(char *));
	g_env->paths = NULL;
	g_env->merged = NULL;
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
	ft_update_shlvl();
	return (g_env);
}
