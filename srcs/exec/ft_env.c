/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 11:36:40 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/02 12:34:50 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

size_t	ft_sizeof(char **env)
{
	size_t		size;

	size = 0;
	while (*env)
	{
		size++;
		env++;
	}
	return (size);
}

static char	**ft_duplicate(char **env)
{
	size_t		size;
	char		**tmp;
	char		**result;

	size = ft_sizeof(env);
	if (!ft_assign(&result, (char **)ft_calloc(size + 1, sizeof(char *))))
		return (NULL);
	tmp = result;
	while (*env)
	{
		*tmp = ft_strdup(*env);
		tmp++;
		env++;
	}
	return (result);
}

t_env	*ft_env(char **env)
{
	t_env	*result;

	if (!ft_assign(&result, (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	result->env = ft_duplicate(env);
	g_exit_code = 0;
	init_paths(result);
	return (result);
}

void	init_paths(t_env *env)
{
	char	**ev;

	ev = env->env;
	while (*ev)
	{
		if (!ft_strncmp(*ev, "PATH=", 5))
		{
			env->paths = ft_split(*ev + 5, ':');
			return ;
		}
		ev++;
	}
	free_splitted(env->paths);
	env->paths = NULL;
}

void	free_env(t_env *env)
{
	free_splitted(env->env);
	if (env->paths)
		free_splitted(env->paths);
	free(env);
}
