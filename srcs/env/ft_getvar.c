/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 07:29:24 by gboucett          #+#    #+#             */
/*   Updated: 2020/12/30 07:55:25 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

char	**ft_find_str(char **strs, char *str)
{
	while (*strs)
		if (!ft_strcmp(*strs++, str))
			return (strs - 1);
	return (NULL);
}

char	*ft_getvar(t_env *env, char *name)
{
	char	**found;

	found = ft_find_str(env->names, name);
	if (!found)
		return (NULL);
	return (env->values[found - env->names]);
}
